# 6. How a UI Click Reaches FSG then Forwards to ASG

This is the end-to-end, byte-by-byte trace of what happens when a user clicks a
button in the web UI. It ties together every other document.

**Full chain:**

```
Browser click
  → React ClientViewHandler.tsx
  → ClientRequestHandler.handleRequest()      → JSON over WebSocket
  → SocketHandler.ts  (Node, :8080)
  → FsgSimulationManager.handleHttpRequest()  → pack bytes, swap pairs
  → SimulationHandler.executeRequest()        → Windows Named Pipe write
  → HttpRequestHandler.cpp  (C++, pipe server) → read opcode+payload
  → BapParser::encode_*()                     → update DataBase + write_*()
  → FsgIpv6::write_*()                        → BAP_Request*()
  → BPL / BCL → BAP_CANUBS_TxData (SoAd frame)
  → BAP_Transmit_TxData (C++ bridge)
  → PDUManager::insertPDU + sendPDU
  → MulticastSocket::sendLoop → UDP multicast ff14::1:fe:42514
  → ASG-Client receives and feeds its BAP stack
```

---

## 6.1 Step 1 — The React component (`ClientViewHandler.tsx`)

Every control follows the same pattern. Example: **HVAC Power** toggle.

```tsx
const HvacPowerStatus = () => {
    // subscribe to receive state pushed back from the server
    useEffect(() => {
        globalClientRequestHandler.subcribe(
            ComponentIndex_t.MODIFY_HVAC_POWER_STATUS,
            (status: any) => setStatus(!!status)
        );
    }, []);

    const handleSubmit = (e: FormEvent) => {
        e.preventDefault();
        // SEND the new value to the server
        globalClientRequestHandler.handleRequest(
            ComponentIndex_t.MODIFY_HVAC_POWER_STATUS,  // topic
            status                                       // value
        );
    };

    return (
        <form onSubmit={handleSubmit}>
            <select value={...} onChange={...}>
                <option value="true">ON</option>
                <option value="false">OFF</option>
            </select>
            <button type="submit">SEND</button>
        </form>
    );
};
```

`handleRequest` (in `ClientRequestHandler.ts`) wraps the values as JSON and
sends over the WebSocket:

```ts
handleRequest(request_id, ...data) {
    const data_json = { targetId: request_id, payload: data };
    globalClientSocketHandler.sendRequest(JSON.stringify(data_json));
}
```

For HVAC power, the frame on the wire is:

```json
{ "targetId": "MODIFY_HVAC_POWER_STATUS", "payload": [true] }
```

---

## 6.2 Step 2 — WebSocket to Node (`SocketHandler.ts`)

```ts
ws.on('message', (data) => {
    const { targetId, payload } = JSON.parse(data.toString());
    globalFsgSimulationManager.handleHttpRequest(targetId, payload);
});
```

---

## 6.3 Step 3 — Node dispatch + byte packing (`FsgSimulationManager.ts`)

```ts
public handleHttpRequest(request_t: any, payload: any[]): void {
    // 1) swap adjacent pairs (UI packing quirk)
    for (let i = 0; i < payload.length - 1; i += 2) {
        [payload[i], payload[i + 1]] = [payload[i + 1], payload[i]];
    }
    switch (request_t) {
        case ComponentIndex_t.MODIFY_HVAC_POWER_STATUS:
            this._changeHvacPowerStatus(payload[0]);
            break;
        ...
    }
}

private _changeHvacPowerStatus(status: boolean): void {
    const payload = new Uint8Array(2);
    payload[0] = HttpRequest_t.MODIFY_HVAC_POWER_STATUS;   // 0x01
    payload[1] = +status;                                   // 0x01 (ON) or 0x00 (OFF)
    this.m_simulationHandler.executeRequest(payload);
}
```

**The byte payload written toward the FSG:**

| Byte index | Value             | Meaning              |
|-----------|-------------------|----------------------|
| `0`       | `0x01`            | opcode MODIFY_HVAC_POWER_STATUS |
| `1`       | `0x01` / `0x00`   | power on / off        |

---

## 6.4 Step 4 — Named Pipe write (Node → C++)

`SimulationHandler.ts` opens the Windows Named Pipe and writes the raw bytes:

```ts
const PIPE_NAME = '\\.\pipe\MyTerminalPipe';
// BINARY_PATH = simulation_executable_file/fsg_ipv6_multicast.exe

public executeRequest(payload: Uint8Array): void {
    fs.open(PIPE_NAME, 'w', (err, fd) => {
        fs.write(fd, payload, 0, payload.length, null, (writeErr) => {
            fs.close(fd, () => {});
        });
    });
}
```

> The pipe is **byte-mode, inbound, overlapped**, named `\\.\pipe\MyTerminalPipe`.

---

## 6.5 Step 5 — Named Pipe read (C++ server)

`HttpRequestHandler.cpp` runs a thread that creates a pipe instance and waits
for a client:

```cpp
#define PIPE_NAME L"\\\\.\\pipe\\MyTerminalPipe"
#define BUFFER_SIZE 1024

// ... in start():
HANDLE hPipe = CreateNamedPipeW(
    PIPE_NAME,
    PIPE_ACCESS_INBOUND | FILE_FLAG_OVERLAPPED,
    PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
    PIPE_UNLIMITED_INSTANCES,
    BUFFER_SIZE, BUFFER_SIZE, 0, NULL);

// overlapped ConnectNamedPipe ... then read loop
ReadFile(hPipe, buffer + totalBytesRead, BUFFER_SIZE - 1 - totalBytesRead,
         &bytesRead, &olRead);
```

It accumulates bytes. The **first byte** is the request type; once it knows the
type it computes `requiredSize` (the total payload length it must wait for):

```cpp
case static_cast<uint8_t>(httpReq::MODIFY_HVAC_STATUS):
    // 1 byte ID + 1 byte cmd
    requiredSize = 2u;
    break;
case static_cast<uint8_t>(httpReq::MODIFY_AC_COMPRESSOR_STATUS):
    requiredSize = 4u;   // ID + status + modi_state + modi_reason
    break;
case static_cast<uint8_t>(httpReq::MODIFY_HVAC_TEMP_ZL):
    requiredSize = 8u;   // ID + 4B float temp + unit + modi_state + modi_reason
    break;
...
case static_cast<uint8_t>(httpReq::MODIFY_TIRE_PRESSURE):
    requiredSize = 18u;  // ID + unit + 4×float32
    break;
case static_cast<uint8_t>(httpReq::MODIFY_SEAT_CLIMATE_ZL):
    requiredSize = 5u;   // ID + heat_val + heat_state + vent_val + vent_state
    break;
```

The full **per-opcode payload table** (pipe → C++):

| Opcode | Name                    | Size | Payload layout (after opcode byte)             |
|--------|-------------------------|------|-----------------------------------------------|
| `0x01` | MODIFY_HVAC_STATUS      | 2    | `cmd`                                          |
| `0x02` | MODIFY_AC_COMPRESSOR_STATUS | 4 | `status`, `modi_state`, `modi_reason`          |
| `0x03` | MODIFY_AC_COMPRESSOR_ECO_MAX | 4 | `mode`, `modi_state`, `modi_reason`          |
| `0x04` | MODIFY_HVAC_TEMP_ZL     | 8    | `float32 temp`, `unit`, `modi_state`, `modi_reason` |
| `0x05` | MODIFY_HVAC_TEMP_ZR     | 8    | `float32 temp`, `unit`, `modi_state`, `modi_reason` |
| `0x06` | MODIFY_HVAC_FAN_SPEED_ZL | 4   | `volume`, `modi_state`, `modi_reason`          |
| `0x07` | MODIFY_HVAC_FAN_SPEED_ZR | 4   | `volume`, `modi_state`, `modi_reason`          |
| `0x08` | MODIFY_RVC              | 2    | `cmd` (not implemented)                        |
| `0x09` | MODIFY_TIRE_PRESSURE    | 18   | `unit`, `float32 fl`, `fr`, `rl`, `rr`         |
| `0x0A` | MODIFY_SEAT_CLIMATE_ZL  | 5    | `heat_state`, `heat_val`, `vent_state`, `vent_val` |
| `0x0B` | MODIFY_SEAT_CLIMATE_ZR  | 5    | `heat_state`, `heat_val`, `vent_state`, `vent_val` |
| `0x0C` | MODIFY_AIR_CIRC_MANUAL  | 2    | `cmd`                                          |
| `0x0D` | MODIFY_AIR_DIST_ZL      | 2    | `distribution_state`                           |
| `0x0E` | MODIFY_AIR_DIST_ZR      | 2    | `distribution_state`                           |

Once `totalBytesRead >= requiredSize`, it extracts fields with `memcpy`
(floats are raw little-endian `float32` on Windows) and calls the parser.

For HVAC power:

```cpp
uint8_t raw_bool_val = 0;
std::memcpy(&raw_bool_val, buffer + 1, sizeof(uint8_t));
const bool power_status = (raw_bool_val != 0u);
parser->encode_hvac_power(power_status);
```

---

## 6.6 Step 6 — `BapParser::encode_*()` (UI command → BAP request)

This is where the UI value is turned into the actual BAP byte layout defined by
the Volkswagen function-spec PDFs. Each encode:

1. Stores the value into the `http::` defaults (so the UI can echo it back),
2. Reads the **current value** from the `DataBase`,
3. **Bit-encodes** the new value according to the spec,
4. Writes it back to the `DataBase` (`storeData`),
5. Calls the matching `FsgIpv6::write_*()` which issues a `BAP_Request*`.

### 6.6.1 HVAC power — `encode_hvac_power`

Per `BAP-FC_ClimateZone_P30DF7.17_V5.17.0_F.pdf` **page 29**, **bit 4** of the
FSG_Control Uint8 means on/off:

```cpp
void BapParser::encode_hvac_power(const bool cmd) {
    http::hvac_power_status = cmd;
    auto [data, len] = fsg->loadData<uint8_t>(
        lsgId_t::BapLsg_ClimateZone,               // 0x01
        fctId_t::BapFct_ClimateZone_FSG_Control);  // FSG_Control

    if (cmd)      data |= (1 << 4);   // set bit 4 → ON
    else          data &= ~(1 << 4);  // clear bit 4 → OFF

    fsg->storeData<uint8_t>(lsgId_t::BapLsg_ClimateZone,
                            fctId_t::BapFct_ClimateZone_FSG_Control,
                            {data, len});
    fsg->write_hvac_power_status(data);   // → BAP_RequestInt8
}
```

### 6.6.2 AC compressor status — `encode_ac_compressor_status`

Per `BAP-FC_ClimateMaster_P31DF3.19_V1.19.0_F.pdf` **pages 38–41**, byte 0 is a
bitfield and the last byte holds modification state + reason:

```cpp
// byte 0 bits: bit0=AC ON/OFF, bit1=MAX, bit2=ECO, bit3=MAX rear, 4-7 reserved
if (status)      data[0] |= (1 << 0);
else             data[0] &= ~(1 << 0);

// last byte bit0 = modification state (1=can change)
if (modi_state)  data[len-1] |= (1 << 0);
else             data[len-1] &= ~(1 << 0);
// last byte high nibble = modification reason
data[len-1] &= 0x0F;
data[len-1] |= (uint8_t)(modi_reason << 4);

fsg->storeData<...>(lsgId_t::BapLsg_ClimateMaster,   // 0x42
                    fctId_t::BapFct_ClimateMaster_AC,
                    {data, len});
fsg->write_ac_compressor_status(data);   // → BAP_RequestByteSequence
```

### 6.6.3 Temperature — `encode_temp_zl / _zr`

Per spec **pages 42–53**, byte 0 = temperature, byte 1 = unit (0=C, 1=F):

```cpp
const uint8_t temp_cel = (uint8_t)std::round((value - 10.0f) / 0.1f);
data[0] = temp_cel;          // 10.0°C → 0, 22.0°C → 120, ...
data[1] = (uint8_t)unit;     // 0 = Celsius, 1 = Fahrenheit
// last byte = modification state/reason (same as above)
```

### 6.6.4 Fan speed — `encode_fan_speed_zl / _zr`

Per spec **pages 54–65**, the **high nibble** of byte 0 is the manual volume:

```cpp
data[0] &= 0x0F;          // clear high nibble
data[0] |= (value << 4);  // value 0..9 → high nibble
```

### 6.6.5 Seat climate — `encode_seat_climate_zl / _zr`

Per spec **pages 82–91**, byte 0 = heater (low nibble value, high nibble state),
byte 1 = ventilation. Then the data is **reversed** and sent in **6-byte
chunks** (segmentation):

```cpp
data[0] = (heat_val & 0x0F) | ((heat_state & 0x0F) << 4);
data[1] = (ventilation_val & 0x0F) | ((ventilation_state & 0x0F) << 4);

std::vector<uint8_t> convertedData = data;
std::reverse(convertedData.begin(), convertedData.end());
for (int32_t i = 0; i < (len + 6u - 1u) / 6u; i++) {
    auto it_start = convertedData.begin() + (i * 6u);
    auto it_end = min(it_start + 6u, convertedData.end());
    fsg->write_seat_climate_zl(std::vector<uint8_t>(it_start, it_end));
}
```

### 6.6.6 Air circulation — `encode_air_circulation_manual`

Per `BAP-FC_ClimateMaster` **pages 82–83**, **bit 0** of byte 0:

```cpp
uint8_t set_val = data[0] & ~(1 << 0);   // clear bit 0
if (value) set_val |= (1 << 0);          // request cabin air
// else: outside air (bit stays 0)
fsg->write_air_circ_manual(data);        // → BAP_RequestByteSequence (ClimateMaster)
```

### 6.6.7 Air distribution — `encode_air_distribution_zl / _zr`

Per spec **page 73**: byte0 low nibble = BODY, byte0 high nibble = UP, byte1
high nibble = FOOTWELL:

```cpp
data[0] = 0u;  data[1] &= 0x0Fu;
switch (value) {
    case UP:       data[0] |= (12 << 4); break;
    case BODY:     data[0] |= (12 << 0); break;
    case FOOTWELL: data[1] |= (12 << 4); break;
}
fsg->write_air_dist_zl(data);
```

---

## 6.7 Step 7 — `FsgIpv6::write_*()` → `BAP_Request*()`

The `write_*` methods translate a logical function into the BAP request:

```cpp
void FsgIpv6::write_hvac_power_status(const uint8_t value) {
    const BapError_t ret = BAP_RequestInt8(
        lsgId_t::BapLsg_ClimateZone,              // 0x01
        fctId_t::BapFct_ClimateZone_FSG_Control,  // FSG_Control fctId
        BapRequest_t::BapReq_Data,
        value);
}

void FsgIpv6::write_ac_compressor_status(const std::vector<uint8_t> payload) {
    BAP_RequestByteSequence(
        lsgId_t::BapLsg_ClimateMaster,            // 0x42
        fctId_t::BapFct_ClimateMaster_AC,         // AC fctId
        BapRequest_t::BapReq_Data,
        payload.data(), payload.size());
}
```

`BAP_Request*` → `BAP_BAL_CheckRequest` then `BAP_BPL_Send` — the BPL writes the
value into the function's BCL TX buffer and schedules it for transmission.

---

## 6.8 Step 8 — Down the stack and onto the bus (TX path)

1. **BCL** places the frame into the function's BCL TX buffer.
2. **`BAP_CANUBS_TxData(channel=20, pduId, data, len)`** (`palb.c`) sees the
   Ethernet channel `20` and prepends the **SoAd header** into
   `palb_EthTxBuffers[]` (4-byte big-endian message id + 4-byte big-endian length).
3. It calls **`BAP_Transmit_TxData(channel, pduId, frame, len+8)`** — the C++
   bridge in `FsgIpv6.cpp`.
4. `FsgIpv6::transmitTxData()` re-parses the SoAd header and hands the PDU to
   the `PDUManager`:

```cpp
bool_t FsgIpv6::transmitTxData(ptr_t apData, const uint16_t au16MsgLength) {
    // parse SoAd header
    const uint32_t msg_id = (apData[0]<<24)|(apData[1]<<16)|(apData[2]<<8)|apData[3];
    const uint32_t payload_len = au16MsgLength - BAP_SOAD_HEADER_SIZE;
    std::vector<uint8_t> payload(apData + BAP_SOAD_HEADER_SIZE, apData + au16MsgLength);

    m_pduManager->insertPDU({msg_id, payload_len, std::move(payload)});
    m_pduManager->sendPDU();
    return BAP_TRUE;
}
```

5. `insertPDU` caches the PDU keyed by message id and marks it pending;
   `sendPDU` snapshots all pending PDUs and calls
   `MulticastSocket::sendPDUs(pdus)`.
6. `sendPDUs` enqueues the batch; `sendLoop` (background thread) wakes up,
   `serializePDUs()` re-encodes each PDU as `[4B id BE][4B len BE][payload]`,
   and `sendto()`s them to `ff14::1:fe:42514` on the `vEthernet (br0.3)`
   interface.

---

## 6.9 Step 9 — The ASG receives it

The **ASG-Client** joined the same multicast group. Its own `MulticastSocket`
`recvLoop` reads the datagram, `PDUParser::parse` splits it into PDUs, and the
ASG's BAP stack receives the frame for the appropriate message id
(e.g. `0x38000100` for ClimateZone). The ASG sees the new value for that
function — the FSG→ASG forward is complete.

---

## 6.10 Byte-level worked example: toggle HVAC **ON**

1. User clicks **ON** on the HVAC Power card.
2. WebSocket frame:
   `{ "targetId": "MODIFY_HVAC_POWER_STATUS", "payload": [true] }`
3. Node packs → `Uint8Array [0x01, 0x01]` → writes pipe.
4. C++ reads `requiredSize=2`, gets `requestType=0x01`, `buffer[1]=0x01`
   → `power_status = true`.
5. `encode_hvac_power(true)`:
   - `data = loadData<uint8_t>(ClimateZone, FSG_Control)` (some current value)
   - `data |= (1 << 4)`
   - `storeData(...)` + `write_hvac_power_status(data)`
6. `BAP_RequestInt8(0x01, FSG_Control, BapReq_Data, data)`
7. BPL/BCL → `BAP_CANUBS_TxData(20, 100, ...)` → SoAd frame:
   - msg id `38 00 01 00`
   - len `00 00 00 01`
   - payload `[0x1x]` (bit 4 set)
8. `BAP_Transmit_TxData` → `PDUManager` → multicast `ff14::1:fe:42514`
9. **ASG** receives and processes the ClimateZone FSG_Control update.

---

## 6.11 Reverse direction (ASG → FSG → UI)

The same pipeline runs backwards for state coming from the ASG:

```
ASG sends 0x3000… frame
  → FSG recvLoop → parse → onRecv → _onPduReceived → m_rxQueue
  → BAP_RxIndication → BCL ring → BAP_Task → BPL
  → FsgIpv6::indicationInt8 / indicationByteSequence (DataSetGet echo)
  → (decode_* writes into DataBase + http:: defaults)
  → UI polls or is pushed the value back over WebSocket
```

`decode_hvac_power` (in `BapParser.cpp`) reads bit 4 and stores it for the UI:

```cpp
void BapParser::decode_hvac_power(const uint8_t status) {
    const bool gt_hvac_power_val = (bool)((1 << 4) & status);
    http::hvac_power_cmd = gt_hvac_power_val;   // this will be sent to HTTP view
}
```

---

## 6.12 Full chain diagram (one click)

```
[Browser]
  React control → handleRequest("MODIFY_HVAC_POWER_STATUS", true)
        │  JSON {targetId, payload}
        ▼
[Node :8080]  SocketHandler ws 'message' → FsgSimulationManager.handleHttpRequest
        │  swap pairs → _changeHvacPowerStatus(true)
        │  payload = [0x01, 0x01]
        ▼
[Node]  SimulationHandler.executeRequest → fs.open(\\.\pipe\MyTerminalPipe) → fs.write
        ▼
[C++]   HttpRequestHandler: CreateNamedPipe + ReadFile → requiredSize=2
        │  requestType=0x01, power=true
        ▼
[C++]   BapParser::encode_hvac_power(true)
        │  data |= (1<<4); storeData; write_hvac_power_status(data)
        ▼
[C++]   BAP_RequestInt8(0x01, FSG_Control, BapReq_Data, data)
        │  BPL → BCL TX buffer
        ▼
[C++]   BAP_CANUBS_TxData(20, pduId=100, ...)
        │  palb_AddSoAdHdr → frame [38 00 01 00 | 00 00 00 01 | payload]
        ▼
[C++]   BAP_Transmit_TxData → PDUManager::insertPDU + sendPDU
        │
        ▼
[C++]   MulticastSocket::sendLoop → UDP multicast ff14::1:fe:42514
        ▼
[ASG]   ASG-Client receives frame → its BAP stack processes the update
```

*Document written from `ClientViewHandler.tsx`, `ClientRequestHandler.ts`,
`SocketHandler.ts`, `FsgSimulationManager.ts`, `SimulationHandler.ts`,
`HttpRequestHandler.cpp`, `BapParser.cpp`, `FsgIpv6.cpp`, `palb.c`,
`PDUManager.cpp`, and `MulticastSocket.cpp`.*
