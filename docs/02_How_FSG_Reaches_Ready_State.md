# 2. How the FSG Becomes "Ready" / Running

This document explains the state machine that brings each LSG from *nothing* to
*fully running and talking to the ASG*, and how the C++ server verifies that it
is truly ready before continuing.

---

## 2.1 The per-LSG state machine

Every LSG lives in one of these states (enum `BapLayerLsgStatus_et`):

```
BapLayerLsgStat_NoInit
        │  BAP_Init()                       (allocates buffers, copies ROM)
        ▼
BapLayerLsgStat_Initialized
        │  BAP_Start()                      (FSG: sends BAPConfig, transitions)
        ▼
BapLayerLsgStat_Running                     ← "ready"
```

---

## 2.2 Init → `Initialized`

During `init()` (doc #1), `BAP_Init(lsg)` is called. On success the LSG RAM row
status becomes `BapLayerLsgStat_Initialized`. The server logs:

```
[SERVER] Success to init lsgId : 1
[SERVER] Success to init sending buffers
```

If `BAP_Init` fails, `_initLsg()` returns -1 and the whole program aborts with
`Failed to init BAP`.

---

## 2.3 Start → `Running`

`start()` first calls `_startLsg()`. For each LSG it does three things:

1. Calls `BAP_Start(lsg)`.
2. **Polls** `BAP_GetLsgState(lsg)` until it returns TRUE or a 3-second
   timeout expires.
3. Checks the final state and aborts the whole server if not running.

```cpp
int32_t FsgIpv6::_startLsg(void)
{
    for (const lsgId_t lsg : lsgId_vec) {
        // 1) tell the BAP stack to start this LSG
        if (BAP_Start(lsg) != BapError_t::BapErr_OK) { ... return -1; }
        std::cout << "[SERVER] Success to start lsgId : ...\n";

        // 2) poll until Running or timeout (TIMEOUT_AFTER_START_LSG = 3000)
        int32_t timeout = 0;
        while (BAP_GetLsgState(lsg) != BAP_TRUE && timeout < TIMEOUT_AFTER_START_LSG) {
            _waitBAPTasks(1);     // run BAP_Task() so TX can drain
            timeout++;
        }

        // 3) verify
        if (BAP_GetLsgState(lsg) != BAP_TRUE) { ... return -1; }
        std::cout << "[SERVER] lsgId : ... , is running !!!\n";
        _waitBAPTasks(1);
    }
    return 0;
}
```

### What `BAP_Start(lsg)` actually does (inside `bap_bal.c`)

`BAP_Start` only proceeds if the LSG is `Initialized`. Then, because this is an
**FSG** (not an ASG):

1. Calls `BAP_BPL_Start()` — starts the Protocol Layer for this LSG.
2. Builds a **BAPConfig** message with `BapOp_PropReset_Set` from the ROM
   default (`BAP_BAPConfigTable`) and sends it to the ASG via
   `BAP_BPL_Send()`. This tells the ASG "here is my configuration", forcing a
   config reset.
3. On success sets `poLsgRamRow->eLsgStatus = BapLayerLsgStat_Running`.
4. On the very first start it also sends a **version-info** frame
   (`OpCode = Status`, LSG-ID 0, FCT-ID 0, `VersionMajor`, `VersionMinor`)
   so the ASG knows the BAP XML protocol version (here 1.0).

### What `BAP_GetLsgState(lsg)` returns

It is a simple predicate:

```c
BAP_TRUE  if eLsgStatus == BapLayerLsgStat_Running
BAP_FALSE otherwise
```

So "**ready**" in the code means: *the BAP stack accepted the LSG into the
Running state and was able to transmit the initial BAPConfig frame onto the
bus.*

> Why poll instead of assuming `BAP_Start` returned OK? Because the BAPConfig
> frame must actually be **drained** out through the TX path (`BAP_Task()`).
> `_waitBAPTasks(1)` runs `BAP_Task()` so that pending TX is flushed; only then
> is the LSG considered truly live. The 3 s timeout guards against a stuck or
> unavailable bus.

---

## 2.4 After all LSGs are running — the rest of startup

Once every LSG is Running, `start()` continues:

```cpp
void FsgIpv6::start(void)
{
    const int32_t ret_start_lsg = _startLsg();
    if (ret_start_lsg != 0) return;

    // bring up the multicast transport (with retry)
    int32_t retry = 0;
    while (!m_pduManager->isMulticastRunning()) {
        if (m_pduManager->startMulticast()) { break; }      // join group + threads
        retry++;
        Sleep(1000);                                        // retry every 1s
    }

    _genDataBase();          // build the in-memory mirror (doc #1.4)
    _sendInitialValue();     // push defaults to the ASG (doc #6)
    m_bapRunning.store(true);
    _heartBeat();            // start the 1s heartbeat thread (doc #4)
    _startHttpHandler();     // start the Named Pipe server (doc #6)

    while (m_bapRunning.load()) {
        _waitBAPTasks(1);    // main loop: drain RX + tick BAP + sleep 200ms
    }
}
```

### Order matters

1. LSGs must be **Running** before the multicast socket starts, so the very
   first frame (BAPConfig) can already go out.
2. The multicast socket is started with a **retry loop** (1 s interval) until
   it succeeds — the VLAN interface may not be ready immediately.
3. `_sendInitialValue()` runs **after** buffers + database exist, encoding the
   current UI defaults into BAP and sending them (doc #6).
4. `_heartBeat()` keeps each LSG alive toward the ASG (doc #4).

---

## 2.5 The "ready" checklist (summary)

For the FSG to be fully *ready*:

| # | Condition                                  | Set by                       | Failure if |
|---|--------------------------------------------|------------------------------|------------|
| 1 | Every LSG `Initialized`                    | `BAP_Init` in `_initLsg`     | abort init |
| 2 | Every LSG `Running` + BAPConfig drained    | `BAP_Start` + poll in `_startLsg` | abort start |
| 3 | Multicast socket joined group `ff14::1:fe:42514` | `startMulticast()` (retry loop) | server exits early |
| 4 | DataBase mirror built                       | `_genDataBase()`             | log error |
| 5 | Initial values sent to ASG                 | `_sendInitialValue()`        | log error |
| 6 | Heartbeat thread running (1 Hz)            | `_heartBeat()`               | ASG times out later |
| 7 | Named Pipe server listening                | `_startHttpHandler()`        | UI commands won't arrive |

Only after all seven is the server said to be "**running**" and the main BAP
task loop is entered.

---

## 2.6 Sequence diagram

```
 main()        _startLsg()        BAP_Start()        BAP stack         multicast
   │               │                  │                  │                │
   │  BAP_Start()  │─────────────────►│ BAP_Start        │                │
   │               │                  │ ─► BPL_Start     │                │
   │               │                  │ ─► send BAPConfig│──► frame ─────►│
   │               │                  │ ─► status=Running│                │
   │               │                  │                  │                │
   │ BAP_GetLsgState() loop (poll, up to 3 s) ◄────────────────────────────│
   │               │    while not Running: _waitBAPTasks(1)                │
   │               │                                                       │
   │ startMulticast() ────────────────────────────────────────────────────►│ join group
   │ _genDataBase()      (mirror)                                          │
   │ _sendInitialValue() (defaults → ASG) ─────────────► frames ─────────►│
   │ _heartBeat()        (1 Hz thread)      ─────────────► HB frames ────►│
   │ _startHttpHandler() (Named Pipe server)                              │
   │ main loop: _waitBAPTasks(1) forever                                   │
```

*Document written from `FsgIpv6.cpp` (`_startLsg`, `start`) and the BAP stack
(`bap_bal.c`).*
