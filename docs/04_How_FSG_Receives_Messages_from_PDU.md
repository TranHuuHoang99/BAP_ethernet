# 4. How the FSG Receives Messages from the PDU

This document traces a frame that arrives on the multicast bus, all the way
from the raw UDP datagram to the BAP stack raising an indication in the C++
application. This is the **FSG ← ASG** direction (commands/requests from the
ASG).

---

## 4.1 The receive thread: `recvLoop()`

`MulticastSocket` runs a background thread `recvLoop()` that continuously reads
UDP datagrams:

```cpp
void MulticastSocket::recvLoop() {
    std::vector<uint8_t> buffer(kMaxDatagramSize);   // 64 KB
    struct pollfd pfd;
    pfd.fd = recieve_sockfd_;                        // the :42514 membership socket
    pfd.events = POLLIN;

    while (running_.load()) {
        int rv = socket_wrapper_->poll(&pfd, 1, 500);   // wait up to 500 ms
        if (rv <= 0) continue;                           // timeout -> re-check running_
        if (pfd.revents & (POLLERR|POLLHUP|POLLNVAL)) break;  // error/hangup
        if (pfd.revents & POLLIN) {
            ssize_t n = recvfrom(recieve_sockfd_, buffer.data(), buffer.size(), 0, ...);
            if (n <= 0) continue;

            // ONE datagram may contain SEVERAL PDUs
            auto pdus = PDUParser::parse(buffer.data(), (size_t)n);
            if (!pdus.empty() && recv_callback_)
                recv_callback_(pdus);     // → PDUManager::onRecv
        }
    }
}
```

The callback was set in the `PDUManager` constructor:

```cpp
socket_.setReceiveCallback(std::bind(&PDUManager::onRecv, this, _1));
```

---

## 4.2 PDU parsing: `PDUParser::parse()`

`pdu_parser.cpp` splits the raw datagram into one or more **PDUs**, each
headed by an 8-byte SoAd header (4-byte big-endian message id + 4-byte
big-endian length):

```cpp
std::vector<PDU> PDUParser::parse(const uint8_t* data, size_t length) {
    std::vector<PDU> pdus;
    size_t offset = 0;
    while (offset + 8 <= length) {               // need a full header
        PDU pdu;
        std::memcpy(&pdu.message_id, data + offset, 4);       // 4B id
        std::memcpy(&pdu.length,     data + offset + 4, 4);   // 4B len
        offset += 8;

        pdu.message_id = be32_to_host(pdu.message_id);        // big-endian → host
        pdu.length     = be32_to_host(pdu.length);

        if (offset + pdu.length > length) return {};          // truncated → bail

        pdu.payload.resize(pdu.length);
        std::memcpy(pdu.payload.data(), data + offset, pdu.length);
        offset += pdu.length;

        pdus.push_back(pdu);
    }
    return pdus;
}
```

A `PDU` is:

```cpp
// pdu.h
struct PDU {
    uint32_t message_id;
    uint32_t length;
    std::vector<uint8_t> payload;
};
```

---

## 4.3 PDUManager dispatches to registered notifiers: `onRecv()`

`PDUManager::onRecv(pdus)` is called with the parsed batch. For every PDU it:

1. Caches it in `pdus_cache_[message_id]`,
2. Looks up the notifiers registered for that message id,
3. Invokes each notifier callback with the PDU.

```cpp
void PDUManager::onRecv(const std::vector<PDU>& pdus) {
    for (const auto& pdu : pdus) {
        pdus_cache_[pdu.message_id] = pdu;            // cache latest value

        std::vector<Notifier> cbs;
        auto it = notifiers_.find(pdu.message_id);
        if (it != notifiers_.end()) cbs = it->second;

        for (auto& cb : cbs) cb(pdu);                  // fire callbacks
    }
}
```

### Who is registered?

In `FsgIpv6::init()`, notifiers are registered for the **four FSG TX message
ids**:

```cpp
for (const uint16_t msg_id : { BAP_Klima1_FSG_01_MSGID,        // 0x38000100
                               BAP_Klima2_FSG_01_MSGID,        // 0x38000200
                               BAP_KlimaMaster_FSG_01_MSGID,   // 0x38004200
                               BAP_RDK_FSG_01_MSGID })         // 0x38000700
{
    m_pduManager->registerNotifier(msg_id, [this](const PDU& pdu) {
        _onPduReceived(pdu);
    });
}
```

> **Note:** These are the ids the FSG itself transmits. Because the recv socket
> has **multicast loopback enabled** (`IPV6_MULTICAST_LOOP = 1`), the FSG also
> receives its own frames — and the same transport loop feeds them into the BAP
> stack. In this multicast simulation both directions share the group; the
> ASG's frames carry the `0x3000…` ids, but the mechanism is identical.

---

## 4.4 Rebuilding the SoAd header: `_onPduReceived()`

`FsgIpv6::_onPduReceived(pdu)` takes the parsed PDU and **recreates the 8-byte
SoAd header** around the payload, because the BAP stack's RX entry point
(`BAP_RxIndication`) expects the header present. It writes the message id and
length big-endian, then pushes the frame onto a thread-safe RX queue:

```cpp
void FsgIpv6::_onPduReceived(const PDU& pdu)
{
    std::vector<uint8_t> buf(BAP_SOAD_HEADER_SIZE + pdu.payload.size());
    buf[0] = (pdu.message_id >> 24) & 0xFFu;     // SoAd msg id, big-endian
    buf[1] = (pdu.message_id >> 16) & 0xFFu;
    buf[2] = (pdu.message_id >>  8) & 0xFFu;
    buf[3] =  pdu.message_id        & 0xFFu;
    buf[4] = (pdu.length     >> 24) & 0xFFu;     // SoAd length, big-endian
    buf[5] = (pdu.length     >> 16) & 0xFFu;
    buf[6] = (pdu.length     >>  8) & 0xFFu;
    buf[7] =  pdu.length            & 0xFFu;
    std::copy(pdu.payload.begin(), pdu.payload.end(), buf.begin() + BAP_SOAD_HEADER_SIZE);

    std::lock_guard<std::mutex> lk(m_rxMtx);
    m_rxQueue.push(std::move(buf));              // queue for the BAP task
}
```

---

## 4.5 The main loop drains the queue into the BAP stack

The main server loop runs `_waitBAPTasks(1)` forever:

```cpp
void FsgIpv6::_waitBAPTasks(int32_t time_delay)
{
    while (time_delay--) {
        // 1) drain the RX queue (thread-safe swap under mutex)
        std::queue<std::vector<uint8_t>> localQueue;
        { std::lock_guard<std::mutex> lk(m_rxMtx);
          std::swap(localQueue, m_rxQueue); }

        // 2) feed every frame into the BAP stack
        while (!localQueue.empty()) {
            BAP_RxIndication(localQueue.front().data());
            localQueue.pop();
        }

        // 3) tick the BAP stack
        _tickBap();          // → BAP_Task() under m_bapMtx

        Sleep(200);          // 200 ms per cycle on Windows
    }
}
```

`_tickBap()`:

```cpp
void FsgIpv6::_tickBap(void)
{
    std::lock_guard<std::recursive_mutex> lk(m_bapMtx);
    BAP_Task();
}
```

So the RX path is: **network thread** puts frames on `m_rxQueue`; **main BAP
thread** picks them up and calls `BAP_RxIndication`, then runs `BAP_Task()` to
process them.

---

## 4.6 `BAP_RxIndication()` — entering the BAP stack (`palb.c`)

`BAP_RxIndication(apData)` is the BAP PALB layer's wire entry point:

```c
void BAP_RxIndication(ptr_t apData)
{
    uint16_t MsgLen = palb_GetMsgLenfromSoAdHdr(apData + BAP_START_OF_MSG_LEN); // 4B BE length
    uint16_t PduId  = palb_GetPduIdfromSoAdHdr(apData);                          // msg id → pdu id
    uint8_t  ChnlNum = palb_GetRxChnlNumByPdu(PduId);                            // → channel 20
    BAP_CANUBS_RxData(ChnlNum, PduId, &apData[BAP_START_OF_USER_DATA], MsgLen);  // user bytes only
}
```

- `palb_GetMsgLenfromSoAdHdr` reads the 4-byte big-endian length at offset 4.
- `palb_GetPduIdfromSoAdHdr` looks up the message id in
  `palb_EthPduIdConfigTab[]` to get the internal PDU id (e.g. `0x38000100` → 100).
- `BAP_CANUBS_RxData` (in `bap_bcl.c`) copies only the **user bytes**
  (`apData + 8`) into the BCL **RX ring buffer** for that PDU.

---

## 4.7 `BAP_Task()` processes the received data (`bap_controller.c`)

`BAP_Task()` runs the sublayer tasks in order:

```c
void BAP_Task(void)
{
    BAP_BCL_ReadRingbuffer();      // pull received bytes out of the ring buffer
    BAP_BCL_TaskRxNotify();        // notify BPL of received messages
    BAP_BCL_TaskSend();            // flush any queued TX
    BAP_BPL_TaskHeartbeatDispatcher();
    BAP_DBG_Task();
}
```

The **BPL** (BAP Protocol Layer) validates the BAP frame (opcode, length,
protocol) and raises the appropriate **indication** callback up to the
application.

---

## 4.8 The application callbacks (FsgIpv6Callback.cpp)

The BAP stack calls back into the C++ app via the callbacks implemented in
`FsgIpv6Callback.cpp` and forwarded to the `FsgIpv6` singleton:

| BAP callback                | C++ handler                              |
|-----------------------------|------------------------------------------|
| `BAP_IndicationInt8`        | `FsgIpv6::indicationInt8`                |
| `BAP_IndicationInt16`       | `FsgIpv6::indicationInt16`               |
| `BAP_IndicationInt32`       | `FsgIpv6::indicationInt32`               |
| `BAP_IndicationByteSequence`| `FsgIpv6::indicationByteSequence`        |
| `BAP_IndicationVoid`        | `FsgIpv6::indicationVoid`                |
| `BAP_IndicationError`       | `FsgIpv6::indicationError`               |
| `BAP_Acknowledge`           | `FsgIpv6::acknowledge`                   |
| `BAP_SendDebugInfo`         | `FsgIpv6::sendDebugInfo`                 |

The two that do something real implement the **ACK echo** back to the ASG:

```cpp
// Uint8 data received
void FsgIpv6::indicationInt8(lsgId_t aLsgId, fctId_t aFctId,
                             BapIndication_t aeIndication, uint8_t au8Value)
{
    if (aeIndication == BapIndication_t::BapInd_DataSetGet) {
        BAP_RequestInt8(aLsgId, aFctId, BapRequest_t::BapReq_Data, au8Value);
        // echo the value back as a Data request → ASG
    }
}

// ByteSequence data received
void FsgIpv6::indicationByteSequence(lsgId_t aLsgId, fctId_t aFctId,
                                     BapIndication_t aeIndication,
                                     const volatile uint8_t apValue[],
                                     uint32_t au32Length)
{
    if (aeIndication == BapIndication_t::BapInd_DataSetGet) {
        BAP_RequestByteSequence(aLsgId, aFctId, BapRequest_t::BapReq_Data,
                                (bap_uint8_t*)&apValue[0], au32Length);
        // echo the byte sequence back to the ASG
    }
}
```

This "echo on DataSetGet" is how the FSG acknowledges an ASG `DataSetGet`
request — it re-sends the value it just received, which flows back out through
the TX path (doc #6) to the ASG.

---

## 4.9 Complete RX path diagram

```
 multicast bus
    │  UDP datagram @ ff14::1:fe:42514 (contains 1..n PDUs)
    ▼
 MulticastSocket::recvLoop()
    │  poll → recvfrom → PDUParser::parse()  (split into PDUs)
    ▼
 PDUManager::onRecv(pdus)
    │  cache each PDU + fire notifiers for its message_id
    ▼
 FsgIpv6::_onPduReceived(pdu)
    │  rebuild SoAd header (msg id + length, big-endian)
    │  push frame onto m_rxQueue  (under m_rxMtx)
    ▼
 FsgIpv6::_waitBAPTasks()  [main thread]
    │  drain m_rxQueue → BAP_RxIndication(frame)
    ▼
 BAP_RxIndication()  (palb.c)
    │  parse SoAd header → PduId → channel 20
    ▼
 BAP_CANUBS_RxData(20, pduId, userBytes, len)   (bap_bcl.c)
    │  copy into BCL RX ring buffer
    ▼
 BAP_Task()   (bap_controller.c)
    │  BCL_ReadRingbuffer → BCL_TaskRxNotify → BPL validates
    ▼
 BPL raises indication → FsgIpv6::indicationInt8 / indicationByteSequence / ...
    │  (DataSetGet → echo back via BAP_Request* → ASG)
```

*Document written from `MulticastSocket.cpp`, `pdu_parser.cpp`, `PDUManager.cpp`,
`FsgIpv6.cpp`, `palb.c`, `bap_bcl.c`, `bap_controller.c`, `FsgIpv6Callback.cpp`.*
