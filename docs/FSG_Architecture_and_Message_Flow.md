# FSG (Front-Subordinate Gateway) — Architecture & Message Flow

> Applies to the two projects:
> - `IPv6_Multicast` — the C/C++ FSG server (BAP stack + Ethernet PDU transport + Named Pipe server).
> - `runtime_fsg_simulation` — the Node.js wrapper (WebSocket gateway + HTTP UI host + process supervisor + Named Pipe client).

This document explains, in as much detail as possible, how the FSG simulation
system works end-to-end: from a mouse click on the web UI, through a WebSocket
message, through a Windows Named Pipe, through the C++ FSG server, down into the
BAP protocol stack, and finally out onto the IPv6 multicast bus toward the ASG.

---

## 1. System Overview / Component Map

```
┌──────────────────────────────  BROWSER  ─────────────────────────────┐
│  React UI (ClientViewHandler.tsx)  ◄── HTTP :8081 (static files)     │
│        │  WebSocket ws://host:8080 (SocketHandler.ts)                │
└────────┼──────────────────────────────────────────────────────────────┘
         │  JSON { targetId, payload }
┌────────▼──────────────────────────────────────────────────────────────┐
│  Node.js — runtime_fsg_simulation (the "wrapper"/simulation server)   │
│   • SocketHandler.ts          : WebSocketServer on :8080              │
│   • FsgSimulationManager.ts   : dispatches requests, health check     │
│   • SimulationHandler.ts      : spawns the .exe, writes to Named Pipe │
│   • HttpRequestHandler.ts     : HTTP server serving the UI on :8081   │
└────────┬──────────────────────────────────────────────────────────────┘
         │  Windows Named Pipe  \\.\pipe\MyTerminalPipe
┌────────▼──────────────────────────────────────────────────────────────┐
│  C/C++ — IPv6_Multicast  (fsg_ipv6_multicast.exe)                     │
│   main.cpp ─► FsgIpv6 (singleton)                                     │
│     ├─ HttpRequestHandler.cpp : Named Pipe SERVER (reads commands)    │
│     ├─ PDUManager + MulticastSocket : IPv6 multicast transport        │
│     ├─ FsgDataBase : in-memory value store per (lsgId, fctId)         │
│     ├─ BapParser : HTTP command → BAP encode/decode                   │
│     └─ BAP stack (BAL / BPL / BCL / PALB) + generated fsg.c           │
└────────┬──────────────────────────────────────────────────────────────┘
         │  IPv6 multicast group  ff14::1:fe :42514
┌────────▼──────────────────────────────────────────────────────────────┐
│  ASG-Client (ASGLarge)  — joins the same multicast group              │
│  receives SoAd-framed BAP PDUs, runs its own BAP stack                │
└───────────────────────────────────────────────────────────────────────┘
```

**Two kinds of "server" must be kept distinct:**
1. The **Node.js server** (`runtime_fsg_simulation`) is a management/UI layer.
   It supervises the C++ binary, talks to browsers over WebSocket, and forwards
   UI commands to the binary through a Named Pipe.
2. The **C++ FSG server** (`IPv6_Multicast`) is the *real* FSG. It owns the BAP
   protocol stack and the actual multicast communication with the ASG.

Both are started by running the Node.js server; the Node server launches the
`.exe` on demand (see Health Check in §9).

---

## 2. Ports / Addresses / Channels Summary

| Item                          | Value                              | Defined in                                    |
|-------------------------------|------------------------------------|-----------------------------------------------|
| IPv6 multicast group          | `ff14::1:fe`                       | `FsgIpv6.cpp` (MULTICAST_GROUP)               |
| Multicast remote (recv) port  | `42514`                            | `FsgIpv6.cpp` (MULTICAST_PORT)                |
| Multicast local (send) port   | `42993`                            | `FsgIpv6.cpp` (SRC_PORT)                      |
| VLAN sub-interface name       | `vEthernet (br0.3)`                | `FsgIpv6.cpp` (VLAN_IP)                       |
| WebSocket server port         | `8080`                             | `common/common.ts` (FSG_SIMULATION_PORT)      |
| HTTP (UI) server port         | `8081`                             | `common/common.ts` (FSG_HTTP_PORT)            |
| WS server address (client)    | `ws://10.134.197.32:8080`          | `common/common.ts` (SERVER_IP)                |
| Named Pipe                    | `\\.\pipe\MyTerminalPipe`          | `HttpRequestHandler.cpp` + `SimulationHandler.ts` |
| Binary path (spawned)         | `simulation_executable_file/fsg_ipv6_multicast.exe` | `SimulationHandler.ts` |
| BAP "interface channel" (ETH) | `20`                               | `palb_cfg.c`, `BAP_CANUBS_TxData`            |

### SoAd header layout (used on the wire)

Each message on the multicast bus is prefixed with an 8-byte **SoAd header**:

```
| Byte0 | Byte1 | Byte2 | Byte3 | Byte4 | Byte5 | Byte6 | Byte7 | user data... |
└────── SoAd Message ID (big-endian) ──────┘└──── SoAd Length (big-endian) ──┘└──────┘
```

- **Message ID**: 4 bytes, big-endian (MSB first). In the code it is assembled
  as `(id>>24)&0xFF, (id>>16)&0xFF, (id>>8)&0xFF, id&0xFF`.
- **Length**: 4 bytes, big-endian, = number of **user data bytes** that follow
  (NOT including the header).

Constants `BAP_SOAD_HEADER_SIZE` (=8), `BAP_SOAD_MSGID_SIZE` (=4),
`BAP_SOAD_MSGLEN_SIZE` (=4), `BAP_START_OF_USER_DATA` (=8) come from `bap_canubs.h`.

### The 4 logical devices (LSGs) the FSG hosts

| LSG Id | Name          | TX Msg ID (FSG→ASG) | RX Msg ID (ASG→FSG) |
|--------|---------------|---------------------|---------------------|
| `0x01` | ClimateZone   | `0x38000100` (BAP_Klima1_FSG_01)  | `0x30000100` (BAP_Klima1_ASG_01) |
| `0x42` | ClimateMaster | `0x38004200` (BAP_KlimaMaster_FSG_01) | `0x30004200` (BAP_KlimaMaster_ASG_01) |
| `0x02` | ClimateZone2  | `0x38000200` (BAP_Klima2_FSG_01)  | `0x30000200` (BAP_Klima2_ASG_01) |
| `0x07` | RDK (tyres)   | `0x38000700` (BAP_RDK_FSG_01)     | `0x30000700` (BAP_RDK_ASG_01) |

These mappings live in `palb_cfg_project.h` (MSG IDs) and
`palb_cfg.c` → `palb_EthPduIdConfigTab[]` (PDU ID ↔ MSG ID ↔ interface channel).

---

## 3. How the FSG Creates Its Buffers (BAP Stack Initialization)

Buffer creation is driven by the generated configuration (`fsg.c`, generated
from `fsg.xml` by the Volkswagen **BAPgen** tool) plus the C++ server code in
`FsgIpv6::_initAllSendBuffers`.

### 3.1 The generated configuration tables (fsg.c)

`fsg.xml` declares, for every LSG and every function (fct), the data type and
size of the TX (FSG→ASG) and RX (ASG→FSG) payloads. BAPgen turns this into
compile-time tables in `fsg.c`:

- `BAP_FctRomTables[]` — one `BapFctRomRow_ot` per function. Each row carries:
  - `fctId`, `lsgId`
  - `eTxDataType` (`BapDt_Int8`, `BapDt_Int16`, `BapDt_Int32`,
    `BapDt_ByteSequence`, `BapDt_FixedByteSequence`, `BapDt_Void`)
  - `u32TxSize` — the size in bytes of the TX payload
  - `eFunctionClass` (`BapFctCls_Property`, `BapFctCls_Method`, `BapFctCls_Cache`)
- `BAP_LsgRomTables[]` — one `BapLsgRomRow_ot` per LSG. Each row points into
  `BAP_FctRomTables` via `u16FctRomIndex` and counts functions via `u8FctRomTableSize`.

Examples from the generated table (`fsg.c`):

```
/* LSG#id="1", Function#id="1"  */ {20u, BapSegType_ChannelOneTwoThreeFour, ..., &BCL_TxBuffer0, ...}
/* LSG#id="1", Function#id="13" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer4, ...}
```

Each function row maps to a **BCL TX buffer** (`BCL_TxBuffer0`, `BCL_TxBuffer1`,
…). These are the low-level send buffers owned by the BCL layer.

### 3.2 Init sequence in the server

`main.cpp` calls:

```
FsgIpv6::instance()->init();   // then
FsgIpv6::instance()->start();
```

`init()` (in `FsgIpv6.cpp`) does three things:

1. Creates the `PDUManager` (multicast transport) with the group/ports/VLAN.
2. Registers RX notifiers for the four FSG message IDs (see §5).
3. Creates the `HttpRequestHandler` (Named Pipe server) and the `DataBase`.
4. Calls `_initLsg()`.

#### `_initLsg()` — per-LSG buffer setup

For each LSG in `lsgId_vec` it calls:

```
BAP_Init(lsgId)                       // lower layers init (see below)
_initAllSendBuffers(lsgId)            // create send buffers for every function
```

**`BAP_Init(lsgId)`** (`bap_bal.c`) → `BAP_BAL_Init(FALSE, lsgId)`:
- Looks up the LSG ROM row (`BAP_GetLsgRomRow`).
- Calls `BAP_BPL_Init()` (initializes the BPL sublayer).
- For an FSG, copies the default **FunctionList** and **BAPConfig** ROM values
  into the LSG RAM row (`BAP_aru8FunctionList`, `BapBAPConfig_t`).
- Calls `BAP_BAL_InitFSGBuffers()` to fill the internal function IDs in the
  send buffers.
- Sets the LSG state to `BapLayerLsgStat_Initialized`.

**`_initAllSendBuffers(lsgId)`** (`FsgIpv6.cpp`) is the key buffer-creation
loop. It walks every function row in the LSG's range of `BAP_FctRomTables` and:

- **Skips** functions that need no send buffer:
  - `eFunctionClass == Method` or `Cache`
  - `fctId == 2` (BAP_Config), `fctId == 3` (FunctionList), `fctId == 4` (HeartBeat)
  - `eTxDataType == Void`
- For everything else, dispatches on the TX data type and calls the matching
  BAP API to allocate/init the send buffer, seeding it with zero:

| TX data type            | BAP call                                   | Initial value |
|-------------------------|--------------------------------------------|---------------|
| `BapDt_Int8`            | `BAP_InitSendBufferInt8(lsg, fct, 0)`      | `0x00`        |
| `BapDt_Int16`           | `BAP_InitSendBufferInt16(lsg, fct, 0)`     | `0x0000`      |
| `BapDt_Int32`           | `BAP_InitSendBufferInt32(lsg, fct, 0)`     | `0x00000000`  |
| `BapDt_ByteSequence` / `BapDt_FixedByteSequence` | `BAP_InitSendBufferByteSequence(lsg, fct, zeroBuf, fct.u32TxSize)` | zero vector of `u32TxSize` bytes |

> **Where the buffer lives:** `BAP_InitSendBufferInt8/16/32/ByteSequence`
> (in `bap_bal.c`) validate the request and then call `BAP_BPL_BufferSet()`,
> which writes the initial value down into the BCL TX buffer that the generated
> `fsg.c` table bound to this function. After this call the function has a
> ready-to-send, initialized buffer. Calling `BAP_Request*` later overwrites the
> value in that buffer.

#### The parallel DataBase (in-memory mirror)

`_genDataBase()` + `_genDataFollowLsgId()` build `DataBase`, a
`std::map<lsgId_t, std::map<fctId_t, std::any>>` mirror of the same function
set, also seeded with zeros. It uses the same skip rules. The C++ application
reads (`loadData`) and writes (`storeData`) this map instead of touching the BAP
buffers directly; the two are kept in sync by `BapParser` (see §8).

---

## 4. How the FSG Reaches the "Ready" / Running State

State management is done by the BAP stack through a per-LSG state machine. The
enum is `BapLayerLsgStatus_et`:

```
BapLayerLsgStat_NoInit
  → BapLayerLsgStat_Initialized        (after BAP_Init)
  → BapLayerLsgStat_Running            (after BAP_Start, FSG)
```

### 4.1 The FSG lifecycle

```
init() ──► BAP_Init        → LSG = Initialized, send buffers created
start() ─► BAP_Start       → LSG = Running
         ─► startMulticast() → socket joined, recv/send threads running
         ─► _genDataBase()  → mirror built
         ─► _sendInitialValue() → BapParser pushes defaults out
         ─► _heartBeat()    → heartbeat thread started
         ─► _startHttpHandler() → Named Pipe server thread started
         ─► loop _waitBAPTasks() forever
```

### 4.2 `BAP_Start(lsgId)` — transition to Running

`BAP_Start` (in `bap_bal.c`) checks the state machine: it only proceeds if the
LSG is `Initialized`. Then, because this is an FSG:

- It calls `BAP_BPL_Start()`.
- It builds a **BAPConfig** message (`BapOp_PropReset_Set`) from the copied
  ROM default and sends it via `BAP_BPL_Send()` — this tells the ASG "here is
  my configuration", and forces a reset.
- On success it sets `poLsgRamRow->eLsgStatus = BapLayerLsgStat_Running`.
- It emits a **version info** frame on the first start
  (`OpCode=Status`, LSG-ID=0, FCT-ID=0, `VersionMajor`, `VersionMinor`).

### 4.3 How the server waits for "ready" (`_startLsg`)

`FsgIpv6::_startLsg()` polls readiness:

```cpp
if (BAP_Start(lsg) != BapErr_OK) return -1;
while (BAP_GetLsgState(lsg) != BAP_TRUE && timeout < 3000) {
    _waitBAPTasks(1);   // let BAP_Task() run so TX can drain
    timeout++;
}
if (BAP_GetLsgState(lsg) != BAP_TRUE) return -1;   // not running
```

`BAP_GetLsgState(lsgId)` simply checks whether the LSG RAM row status is
`BapLayerLsgStat_Running` and returns `BAP_TRUE`/`BAP_FALSE`. So "ready" means:
the BAP stack accepted the LSG into Running state **and** was able to transmit
the initial BAPConfig frame (via the multicast socket).

### 4.4 The heartbeat thread

Once running, `_heartBeat()` starts a thread that, every 1000 ms, calls

```cpp
BAP_RequestInt8(lsg, (fctId_t)4, BapRequest_t::BapReq_Data, 0x0A);
```

for every LSG — this sends the HeartBeat function (fctId 4) with value `0x0A`
to the ASG, telling it the FSG is alive. The ASG uses this to keep the LSG
Running and to detect a timeout (`BapErr_TimeoutHeartbeat`).

---

## 5. How the FSG Receives Messages from the PDU (multicast RX path)

This is the "FSG ← ASG" direction (commands / requests coming from the ASG).

### 5.1 Transport: `MulticastSocket`

`MulticastSocket` (`libPDU_MultiPlex`) creates **two** UDP sockets:

1. **Receive socket** — bound to `remote_port` (42514), joins the multicast
   group `ff14::1:fe`, sets `IPV6_JOIN_GROUP` on the interface
   `vEthernet (br0.3)` (resolved to an interface index via `if_nametoindex` /
   Windows LUID helpers). This socket *receives* frames.
2. **Send socket** — bound to `local_port` (42993), hop limit 255, used to
   *send* frames back out.

`start()` launches two background threads:
- `recvLoop()` — `poll()` on the receive fd with a 500 ms timeout; on
  `POLLIN`, calls `recvfrom()` to get one UDP datagram, then
  `PDUParser::parse(buffer, n)` and invokes the receive callback with the
  parsed PDUs.
- `sendLoop()` — waits on a condition variable for queued batches, serializes
  them, and `sendto()`s them.

### 5.2 PDU parsing

`PDUParser::parse()` (`pdu_parser.cpp`) walks the datagram:

```
while (offset + 8 <= length):
    msg_id = be32( bytes[offset..offset+3] )
    length = be32( bytes[offset+4..offset+7] )
    offset += 8
    payload = bytes[offset .. offset+length]
    offset += length
```

It converts the SoAd header fields from big-endian to host order and returns a
`std::vector<PDU>` where each `PDU = { message_id, length, payload }`.

### 5.3 From PDU to the BAP stack

`PDUManager` owns the transport and the RX dispatch:

- `registerNotifier(msg_id, cb)` stores a callback per message ID.
- When `onRecv(pdus)` fires (called by the socket's receive callback), it
  updates `pdus_cache_` and calls every notifier registered for that message ID.

In `FsgIpv6::init()`, notifiers are registered for the four **FSG RX** message
IDs (`BAP_Klima1_FSG_01_MSGID`, etc.) — note: the FSG *transmits* with the
`0x3800…` IDs and *receives* with the `0x3000…` ASG IDs; the notifiers here are
registered for the IDs the FSG uses to talk **to** the ASG because in this
multicast simulation both directions share the group. The registered callback is
`_onPduReceived`.

`_onPduReceived(const PDU& pdu)`:
1. Allocates `buf = BAP_SOAD_HEADER_SIZE + pdu.payload.size()`.
2. Writes the big-endian message ID into `buf[0..3]`.
3. Writes the big-endian length into `buf[4..7]`.
4. Copies `pdu.payload` after the header.
5. Pushes `buf` onto the thread-safe `m_rxQueue`.

### 5.4 Feeding the BAP stack — `BAP_RxIndication`

The main server loop runs `_waitBAPTasks(time_delay)`. Every iteration it:

1. Swaps the shared `m_rxQueue` into a local queue (draining under mutex).
2. For each buffered frame calls **`BAP_RxIndication(frame)`**.
3. Calls `_tickBap()` → `BAP_Task()`.

`BAP_RxIndication()` (`palb.c`) is the entry into the BAP stack from the wire:

```
MsgLen  = palb_GetMsgLenfromSoAdHdr(apData + 4)      // big-endian length
PduId   = palb_GetPduIdfromSoAdHdr(apData)           // msg id → PDU id
ChnlNum = palb_GetRxChnlNumByPdu(PduId)              // → interface channel (20)
BAP_CANUBS_RxData(ChnlNum, PduId, &apData[8], MsgLen)
```

`BAP_CANUBS_RxData` (in `bap_bcl.c`) copies the user bytes into the BCL RX
ring buffer for that PDU. Then `BAP_Task()` (in `bap_controller.c`) runs the
sublayer tasks in order:

```
BAP_BCL_ReadRingbuffer()   // pull bytes out of the ring buffer
BAP_BCL_TaskRxNotify()     // notify BPL of received messages
BAP_BCL_TaskSend()         // send any queued TX
BAP_BPL_TaskHeartbeatDispatcher()
BAP_DBG_Task()
```

The BPL then validates the received BAP frame (opcode, length, protocol) and
raises the appropriate **indication** callback into the application (see §7).

---

## 6. How the FSG Sends Messages to the ASG (multicast TX path)

Whenever the FSG application issues a `BAP_Request*`, the stack eventually calls
`BAP_CANUBS_TxData(channel, pduId, data, length)` (`palb.c`):

1. `palb_GetTxHandleByPdu(pduId)` finds the TX buffer index.
2. Because channel is in `[20,30)` (Ethernet), it calls
   `palb_AddSoAdHdr(index, pduId, data, length)`:
   - resolves the SoAd **Message ID** from the PDU id via `palb_GetMsgId`,
   - writes the 4-byte big-endian message ID,
   - writes the 4-byte big-endian length (= user data length),
   - copies user data into `palb_EthTxBuffers[index]` (a static TX buffer array
     of size `PALB_TX_PDU_COUNT × (BAP_MAX_PDU_SIZE + BAP_SOAD_HEADER_SIZE)`).
3. Calls `BAP_Transmit_TxData(channel, pduId, buffer, length+8)`.

### 6.1 `BAP_Transmit_TxData` → `PDUManager::sendPDU`

`BAP_Transmit_TxData` is implemented in `FsgIpv6.cpp`:

```cpp
bool_t FsgIpv6::transmitTxData(ptr_t apData, uint16_t au16MsgLength)
{
    // parse SoAd header: msg_id (big-endian), payload length
    // build PDU { msg_id, payload_len, payload }
    m_pduManager->insertPDU(pdu);
    m_pduManager->sendPDU();
    return BAP_TRUE;
}
```

- `insertPDU(pdu)` caches the PDU in `pdus_cache_` keyed by message ID and marks
  it pending in `pending_send_ids_`.
- `sendPDU()` snapshots all pending PDUs, calls `MulticastSocket::sendPDUs()`,
  then clears the cache.
- `sendPDUs()` pushes the batch onto `send_queue_` and notifies `sendLoop()`;
  `sendLoop()` serializes via `MulticastSocket::serializePDUs()` (big-endian
  header again) and `sendto()`s it to the group/port.

> **Path summary (TX):**
> BAP application `BAP_Request*` → BPL → BCL buffer → `BAP_CANUBS_TxData`
> → SoAd framing in `palb_EthTxBuffers` → `BAP_Transmit_TxData` (C++) →
> `PDUManager::insertPDU/sendPDU` → `MulticastSocket` → UDP multicast `ff14::1:fe:42514`.

---

## 7. Indication Callbacks: ASG→FSG data reaching the C++ app

When the ASG sends a command and it survives the whole RX path (§5), the BPL
raises a "DataReceived" event. The BAP stack calls the application via
**outgoing callbacks** that the C++ server implements in
`FsgIpv6Callback.cpp`:

| BAP callback                     | C++ handler in `FsgIpv6`                 |
|----------------------------------|------------------------------------------|
| `BAP_IndicationInt8`             | `indicationInt8`                         |
| `BAP_IndicationInt16`            | `indicationInt16`                        |
| `BAP_IndicationInt32`            | `indicationInt32`                        |
| `BAP_IndicationByteSequence`     | `indicationByteSequence`                 |
| `BAP_IndicationVoid`             | `indicationVoid`                         |
| `BAP_IndicationError`            | `indicationError`                        |
| `BAP_Acknowledge`                | `acknowledge`                            |
| `BAP_SendDebugInfo`              | `sendDebugInfo`                          |

Example — `indicationByteSequence` (a function that arrives as a byte array):

```cpp
if (BapIndication_t::BapInd_DataSetGet == aeIndication) {
    BAP_RequestByteSequence(aLsgId, aFctId, BapRequest_t::BapReq_Data,
                            (bap_uint8_t*)&apValue[0], au32Length);
}
```

This pattern (echo the received value straight back as a `Data` request) is how
the FSG **acknowledges** a `DataSetGet` from the ASG — it re-sends the value it
just received, which propagates out through the TX path to the ASG. The same is
done in `indicationInt8` via `BAP_RequestInt8(…, BapReq_Data, au8Value)`.

> In this demo most indication callbacks are empty stubs except `indicationInt8`
> and `indicationByteSequence`, which implement the Uint8 / ByteSequence ACK
> back to the ASG client (see git history: "support response ACK to ASG client
> for Uint8 and ByteSequence").

---

## 8. The WebSocket + UI + Named Pipe pipeline (the request the user asked about)

This is the full chain for **"click a button in the web UI → message reaches the
FSG → forwarded to the ASG"**.

### 8.1 Browser UI (client)

The React UI is defined in `ClientViewHandler.tsx`. Each control is a small
component (e.g. `HvacPowerStatus`, `TemperatureZL`, `AcCompressorForm`, …).
Each one:

1. Subscribes to a server topic via `globalClientRequestHandler.subcribe(topic, cb)`
   so it can receive live updates pushed from the server (used to reflect state
   coming back from the ASG).
2. Renders a `<form>` with `<select>`s and a **SEND** button.
3. On submit calls `globalClientRequestHandler.handleRequest(topic, ...values)`.

`ClientRequestHandler.handleRequest`:

```ts
const data_json = { targetId: request_id, payload: data };
globalClientSocketHandler.sendRequest(JSON.stringify(data_json));
```

`ClientSocketHandler.sendRequest` sends the JSON over the WebSocket
(`ws://10.134.197.32:8080`) when the socket is `OPEN`.

### 8.2 Node server WebSocket gateway

The browser connects to `SocketHandler.ts` (a `ws` WebSocketServer on port
8080). On each `message`:

```ts
const { targetId, payload } = JSON.parse(data.toString());
globalFsgSimulationManager.handleHttpRequest(targetId, payload);
```

### 8.3 Node server dispatch

`FsgSimulationManager.handleHttpRequest`:
1. Swaps each adjacent payload pair:
   `[p0,p1] = [p1,p0]`, `[p2,p3]=[p3,p2]`, … (because the UI packs values in a
   specific order that the binary expects reversed).
2. Switches on the string `targetId` (`ComponentIndex_t`), calls a private
   `_change…` method that **packs the values into a byte payload** whose first
   byte is a numeric `HttpRequest_t` opcode.
3. Calls `m_simulationHandler.executeRequest(payload)`.

Example — HVAC power:

```ts
private _changeHvacPowerStatus(status: boolean) {
    const payload = new Uint8Array(2);
    payload[0] = HttpRequest_t.MODIFY_HVAC_POWER_STATUS; // = 1
    payload[1] = +status;                                 // 0 or 1
    this.m_simulationHandler.executeRequest(payload);
}
```

The opcode numbering (from `request_api.ts`):

```
HttpRequest_t = { INVALID=0, MODIFY_HVAC_POWER_STATUS=1,
  MODIFY_AC_COMPRESSOR_STATUS=2, MODIFY_AC_COMPRESSOR_ECO_MAX=3,
  MODIFY_HVAC_TEMP_ZL=4, MODIFY_HVAC_TEMP_ZR=5, MODIFY_HVAC_FAN_SPEED_ZL=6,
  MODIFY_HVAC_FAN_SPEED_ZR=7, MODIFY_RVC=8, MODIFY_TIRE_PRESSURE=9,
  MODIFY_SEAT_CLIMATE_ZL=10, MODIFY_SEAT_CLIMATE_ZR=11,
  MODIFY_AIR_CIRC_MANUAL=12, MODIFY_AIR_DIST_ZL=13, MODIFY_AIR_DIST_ZR=14 }
```

### 8.4 Named Pipe write (Node → C++)

`SimulationHandler.executeRequest(payload)` opens the Windows Named Pipe
`\\.\pipe\MyTerminalPipe` for writing and writes the raw bytes:

```ts
fs.open(PIPE_NAME, 'w', (err, fd) => {
    fs.write(fd, payload, 0, payload.length, null, (writeErr) => {
        fs.close(fd, () => {});
    });
});
```

### 8.5 Named Pipe read (C++ server)

On the C++ side, `HttpRequestHandler.cpp` runs a thread that loops:
- `CreateNamedPipeW(\\.\pipe\MyTerminalPipe, …)` (byte mode, overlapped,
  unlimited instances).
- `ConnectNamedPipe` (waits for a client).
- Reads bytes until the expected size for the request type is reached.

The **first byte** is the numeric request type; the number of following bytes it
must read depends on the type:

| Request type byte          | Payload bytes after opcode | Meaning                              |
|----------------------------|----------------------------|--------------------------------------|
| `1` MODIFY_HVAC_STATUS     | 1 (cmd)                    | HVAC on/off                          |
| `2` MODIFY_AC_COMPRESSOR_STATUS | 3 (status, modi_state, modi_reason) | AC on/off                    |
| `3` MODIFY_AC_COMPRESSOR_ECO_MAX | 3 (mode, modi_state, modi_reason) | ECO/MAX                       |
| `4` MODIFY_HVAC_TEMP_ZL    | 4 float32 + unit + modi_state + modi_reason | left temp            |
| `5` MODIFY_HVAC_TEMP_ZR    | same as 4                  | right temp                           |
| `6`/`7` fan speed ZL/ZR    | value + modi_state + modi_reason | fan level                    |
| `9` MODIFY_TIRE_PRESSURE   | unit + 4×float32           | tyre pressures                       |
| `10`/`11` seat climate ZL/ZR | heat_val, heat_state, vent_val, vent_state | seat climate        |
| `12` MODIFY_AIR_CIRC_MANUAL | 1 (cmd)                    | circulation                          |
| `13`/`14` air dist ZL/ZR   | 1 (val)                    | air distribution                     |

It then calls the matching **`BapParser`** method, e.g. for HVAC status:

```cpp
parser->encode_hvac_power(power_status);
```

### 8.6 `BapParser` — UI command → BAP request

`BapParser::encode_hvac_power(cmd)` is the canonical example:

```cpp
void BapParser::encode_hvac_power(const bool cmd) {
    http::hvac_power_status = cmd;                    // remember for UI echo
    auto [data, len] = fsg->loadData<uint8_t>(        // read current value from DB
        lsgId_t::BapLsg_ClimateZone, fctId_t::BapFct_ClimateZone_FSG_Control);
    if (cmd) data |= (1 << 4); else data &= ~(1 << 4); // FSG_Control bit4 = on/off
    fsg->storeData<uint8_t>(lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_FSG_Control, {data, len});   // update DB
    fsg->write_hvac_power_status(data);               // push into BAP stack
}
```

So the encode step:
1. updates the `http::` namespace defaults (so the UI can be refreshed),
2. reads the current value from the in-memory `DataBase`,
3. sets/clears the control bits per the BAP data-spec PDF,
4. writes the new value back to the DataBase,
5. calls `FsgIpv6::write_*(…)` which invokes `BAP_Request*`.

`FsgIpv6::write_hvac_power_status(value)`:

```cpp
BAP_RequestInt8(lsgId_t::BapLsg_ClimateZone,
                fctId_t::BapFct_ClimateZone_FSG_Control,
                BapRequest_t::BapReq_Data, value);
```

### 8.7 Into the BAP stack and out to the ASG

`BAP_RequestInt8(…, BapReq_Data, …)` → `BAP_BPL_Send()` → BCL TX buffer →
`BAP_CANUBS_TxData` → SoAd framing → `BAP_Transmit_TxData` (C++) →
`PDUManager::insertPDU/sendPDU` → `MulticastSocket` → **UDP multicast to
`ff14::1:fe:42514`**, where the ASG-Client (which joined the same group) receives
it and feeds its own BAP stack.

> **Full chain, one click:**
> Browser click → React `handleRequest` → WebSocket JSON → `SocketHandler`
> → `FsgSimulationManager.handleHttpRequest` → pack bytes → Named Pipe write →
> C++ `HttpRequestHandler` reads opcode+payload → `BapParser::encode_*` →
> `storeData` + `write_*` → `BAP_Request*` → BPL/BCL → `BAP_CANUBS_TxData`
> → SoAd → `PDUManager` → multicast socket → **ASG**.

---

## 9. Health Check & Process Supervision (Node side)

`FsgSimulationManager` also runs a health-check loop:

```ts
while (true) {
    const data_json = { targetId: ComponentIndex_t.HEALTH_CHECK_FSG_RUNNING,
                        payload: this.m_simulationHandler.isBinaryRunning() };
    this.m_fsgSocketHandler.send(JSON.stringify(data_json));
    await sleep(3000);
}
```

- Every 3 s it pushes the binary's liveness to all WebSocket clients.
- The browser `HealthCheck` component subscribes to that topic and shows
  "System is Running / Stopped".
- The `ON`/`OFF` button sends `HEALTH_CHECK_FSG_RUNNING` with the inverse; the
  server then calls `executeSimulationBinary()` / `stopSimulationBinary()`.
- `SimulationHandler.executeSimulationBinary()` spawns
  `simulation_executable_file/fsg_ipv6_multicast.exe` and pipes its stdout/stderr
  into the Node console; if it exits unexpectedly it **re-spawns after 3 s**.

---

## 10. Directory / File Map (quick reference)

### `IPv6_Multicast` (C++ FSG server)

| File | Role |
|------|------|
| `main.cpp` | Entry: `init()` + `start()` |
| `FSG/Fsgserver/src/FsgIpv6.cpp` | Server orchestration, multicast, buffer init, TX bridge |
| `FSG/Fsgserver/src/FsgIpv6Callback.cpp` | BAP outgoing callbacks → C++ handlers |
| `FSG/Fsgserver/src/handler/BapParser.cpp` | UI command decode → BAP encode (and vice-versa) |
| `FSG/Fsgserver/src/handler/HttpRequestHandler.cpp` | Named Pipe **server** |
| `FSG/Fsgserver/inc/common/FsgDataBase.hpp` | In-memory value store |
| `FSG/Fsgserver/inc/common/FsgDefaultValue.hpp` | `http::` defaults / signal cache |
| `FSG/Fsgserver/inc/common/FsgType.hpp` | shared types |
| `FSG/FsgLarge/fsg.c`, `palb_cfg.c`, `bap_defines.h` | BAPgen output (config tables) |
| `FSG/FsgLarge/fsg.xml` | BAPgen source config |
| `FSG/FsgLarge/palb_cfg_project.h` | SoAd MSG IDs |
| `BAP/...` | The BAP stack: BAL (`bap_bal.c`), BPL (`bap_bpl.c`), BCL (`bap_bcl.c`), PALB (`palb.c`), controller (`bap_controller.c`) |
| `libPDU_MultiPlex/` | `PDUManager`, `MulticastSocket`, `PDUParser` — the multicast transport |

### `runtime_fsg_simulation` (Node.js wrapper + UI)

| File | Role |
|------|------|
| `src/server/main.ts` | Starts the manager |
| `src/server/FsgSimulationManager.ts` | Dispatches WS requests, health check |
| `src/server/handler/SocketHandler.ts` | WebSocketServer on :8080 |
| `src/server/handler/HttpRequestHandler.ts` | Static UI server on :8081 |
| `src/server/handler/SimulationHandler.ts` | Spawns `.exe`, writes Named Pipe |
| `src/client/*` | Browser WebSocket client + React UI |
| `src/common/request_api.ts` | Topic names + numeric opcodes |
| `src/common/common.ts` | Ports / server IP |
| `simulation_executable_file/fsg_ipv6_multicast.exe` | The compiled C++ server |

---

## 11. Key Definitions / Constants Reference

| Constant | Value | Where |
|----------|-------|-------|
| `BAP_SOAD_HEADER_SIZE` | 8 | `bap_canubs.h` |
| `BAP_SOAD_MSGID_SIZE` | 4 | `bap_canubs.h` |
| `BAP_SOAD_MSGLEN_SIZE` | 4 | `bap_canubs.h` |
| `BAP_START_OF_USER_DATA` | 8 | `bap_canubs.h` |
| `BAP_MAX_PDU_SIZE` | 8 | `bap_defines.h` |
| `PALB_TX_PDU_COUNT` | 4 | `palb_cfg.h` |
| `PALB_PDU_CONFIG_TAB_SIZE` | 8 | `palb_cfg.h` |
| Interface channel (Ethernet) | `20` | `palb_cfg.c` |
| `MULTICAST_GROUP` | `ff14::1:fe` | `FsgIpv6.cpp` |
| `MULTICAST_PORT` (recv) | `42514` | `FsgIpv6.cpp` |
| `SRC_PORT` (send) | `42993` | `FsgIpv6.cpp` |
| `VLAN_IP` | `vEthernet (br0.3)` | `FsgIpv6.cpp` |
| `PIPE_NAME` | `\\.\pipe\MyTerminalPipe` | both C++ and Node |

---

*Document written from the source of `IPv6_Multicast` and
`runtime_fsg_simulation`. FSG = Front-Subordinate Gateway; ASG = Application
Subordinate Gateway; BAP = Bedien- und Anzeigeprotokoll (VW's in-vehicle
HMI-control protocol); LSG = Logical (Subordinate) Control Unit; SoAd =
Socket Adaptor framing; PDU = Protocol Data Unit.*
