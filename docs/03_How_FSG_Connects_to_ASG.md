# 3. How FSG Connects to ASG (IPv6 Multicast)

This document explains the network-level connection between the FSG and the
ASG: the IPv6 multicast transport, the socket setup, the addressing, and the
message ids that carry BAP data between the two sides.

---

## 3.1 The transport: one IPv6 multicast group for everyone

The FSG and the ASG communicate over **UDP over IPv6 multicast**. There is no
point-to-point TCP connection — instead **both** join the same multicast group,
and whoever sends on that group is heard by everyone (including loopback). This
mimics the in-vehicle MQB Ethernet broadcast bus.

Key constants (`FsgIpv6.cpp`):

```cpp
static const std::string MULTICAST_GROUP = "ff14::1:fe";
static const uint16_t    MULTICAST_PORT  = 42514u;   // remote/recv port
static const std::string VLAN_IP         = "vEthernet (br0.3)";
static const uint16_t    SRC_PORT        = 42993u;   // local/send port
```

| Constant                 | Value              | Meaning                                   |
|--------------------------|--------------------|-------------------------------------------|
| `MULTICAST_GROUP`        | `ff14::1:fe`       | IPv6 multicast group address              |
| `MULTICAST_PORT` (recv)  | `42514`            | port the socket **binds + receives** on   |
| `SRC_PORT` (send)        | `42993`            | port the socket **binds + sends** from    |
| `VLAN_IP`                | `vEthernet (br0.3)`| the VLAN sub-interface used for multicast |

Both the FSG and the ASG-Client use the same `libPDU_MultiPlex` library, so both
join `ff14::1:fe:42514`.

---

## 3.2 Creating the PDUManager (the transport object)

`FsgIpv6::init()` builds the transport:

```cpp
m_pduManager = std::make_unique<PDUManager>(
    MULTICAST_GROUP,   // group "ff14::1:fe"
    SRC_PORT,          // 42993   (local send)
    MULTICAST_PORT,    // 42514   (remote recv)
    0u,                // VLAN priority
    VLAN_IP            // "vEthernet (br0.3)" local bind interface
);
```

`PDUManager`'s constructor:

```cpp
PDUManager::PDUManager(const std::string& group_addr, uint16_t local_port,
                       uint16_t remote_port, uint32_t vlan_pro,
                       const std::string& local_ip)
    : socket_(group_addr, local_port, remote_port, vlan_pro) {
    if (!local_ip.empty()) socket_.setLocalAddress(local_ip);
    socket_.setReceiveCallback(std::bind(&PDUManager::onRecv, this, _1));
}
```

So it holds a `MulticastSocket`, binds it to the VLAN interface, and registers
its own receive callback. Later `startMulticast()` → `socket_.start()` actually
opens the sockets and launches the recv/send threads.

---

## 3.3 Socket setup (inside `MulticastSocket::setupSocket`)

The `MulticastSocket` creates **two UDP sockets** (this is the *legacy
single-interface* path compiled here, no `MQB_NETWORK_CONFIG_ENABLED`):

### Receive socket (multicast membership)

```cpp
recieve_sockfd_ = socket_wrapper_->socket(AF_INET6, SOCK_DGRAM, 0);  // AF_INET6
setsockopt(recieve_sockfd_, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, ...);

sockaddr_in6 addr6;
addr6.sin6_family  = AF_INET6;
addr6.sin6_port    = htons(remote_port_);   // 42514
addr6.sin6_addr    = in6addr_any;           // bind any
bind(recieve_sockfd_, (sockaddr*)&addr6, sizeof(addr6));

// Join the multicast group on the VLAN interface
struct ipv6_mreq mreq6;
inet_pton(AF_INET6, group_addr_.c_str(), &mreq6.ipv6mr_multiaddr);
unsigned int ifindex6 = if_nametoindex(local_addr_.c_str());   // "vEthernet (br0.3)"
//   Windows fallback: ConvertInterfaceNameToLuidA / ConvertInterfaceAliasToLuid
mreq6.ipv6mr_interface = ifindex6;
setsockopt(recieve_sockfd_, IPPROTO_IPV6, IPV6_JOIN_GROUP, &mreq6, sizeof(mreq6));

int hops = 1;        setsockopt(..., IPV6_MULTICAST_HOPS, &hops, ...);
unsigned int loop = 1; setsockopt(..., IPV6_MULTICAST_LOOP, &loop, ...); // loopback ON
setsockopt(recieve_sockfd_, IPPROTO_IPV6, IPV6_MULTICAST_IF, &ifindex6, ...);
```

Notes:
- `SO_REUSEADDR` lets two processes (FSG + ASG on the same host) bind the same
  port simultaneously.
- **`IPV6_MULTICAST_LOOP = 1`** on the recv socket: the host receives its own
  multicast sends too. This is why the FSG can "see" its own frames (see doc #4).
- The interface index is resolved from the name `vEthernet (br0.3)`; on Windows
  it first tries `if_nametoindex` and falls back to the LUID/alias conversion
  functions from `iphlpapi.h`.

### Send socket (bound to local port 42993)

```cpp
send_sockfd_ = socket_wrapper_->socket(AF_INET6, SOCK_DGRAM, 0);
setsockopt(send_sockfd_, SOL_SOCKET, SO_REUSEADDR, ...);

int send_hops = 255;
setsockopt(send_sockfd_, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &send_hops, ...);
unsigned int loopDisable = 0;
setsockopt(send_sockfd_, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, &loopDisable, ...); // loop OFF for send
setsockopt(send_sockfd_, SOL_SOCKET, SO_PRIORITY, &vlan_pro_, ...);             // VLAN egress prio

sockaddr_in6 saddr6;
saddr6.sin6_family = AF_INET6;
saddr6.sin6_port   = htons(local_port_);   // 42993
bind(send_sockfd_, (sockaddr*)&saddr6, sizeof(saddr6));

unsigned int ifindex6 = if_nametoindex(local_addr_.c_str());
setsockopt(send_sockfd_, IPPROTO_IPV6, IPV6_MULTICAST_IF, &ifindex6, ...);
```

The send socket is a *separate* UDP socket bound to source port `42993`, with
hop limit 255 and the outgoing interface pinned to the VLAN.

### Threads

`socket_.start()` launches:

```cpp
recv_thread_ = std::thread(&MulticastSocket::recvLoop, this);   // reads UDP -> parse -> callback
send_thread_ = std::thread(&MulticastSocket::sendLoop, this);   // serializes queue -> sendto group
```

---

## 3.4 Where the FSG sends to: the group sockaddr

The destination for every `sendto` is the **group address on port 42514**,
built once in the `MulticastSocket` constructor:

```cpp
inet_pton(AF_INET6, "ff14::1:fe", &sin6->sin6_addr);
sin6->sin6_family = AF_INET6;
sin6->sin6_port   = htons(remote_port_);   // 42514
```

`sendLoop()` does:

```cpp
sendto(send_sockfd_, bytes.data(), bytes.size(), 0,
       (sockaddr*)&group_sockaddr_, group_socklen_);
```

Because the send socket has `IPV6_MULTICAST_IF` set to the VLAN interface, the
packet egresses on `vEthernet (br0.3)` toward the group.

---

## 3.5 The message ids: addressing "which device, which direction"

Even on a shared multicast bus, the FSG and ASG tell devices apart by **SoAd
message id** in the first 4 bytes of each frame. The ids are defined in
`palb_cfg_project.h` and mapped through `palb_cfg.c` (`palb_EthPduIdConfigTab[]`).

| LSG          | Id   | FSG→ASG TX msg id   | ASG→FSG RX msg id   | PDU id (FSG TX) | PDU id (FSG RX) |
|--------------|------|---------------------|---------------------|-----------------|-----------------|
| ClimateZone  | `0x01` | `0x38000100` (`BAP_Klima1_FSG_01`) | `0x30000100` | 100 | 0 |
| ClimateZone2 | `0x02` | `0x38000200` (`BAP_Klima2_FSG_01`) | `0x30000200` | 102 | 2 |
| RDK (tyres)  | `0x07` | `0x38000700` (`BAP_RDK_FSG_01`)    | `0x30000700` | 103 | 3 |
| ClimateMaster| `0x42` | `0x38004200` (`BAP_KlimaMaster_FSG_01`) | `0x30004200` | 101 | 1 |

- The **`0x3800…`** prefix = FSG → ASG (FSG transmits, ASG receives).
- The **`0x3000…`** prefix = ASG → FSG (ASG transmits, FSG receives).
- The middle bytes encode the device (`0x01`, `0x02`, `0x07`, `0x42`); the
  `00` suffix is the frame index within that device.

In `palb_cfg.c` every PDU row maps to the Ethernet interface channel `20`:

```c
/* Klima1 FSG msg id 0x38000100, PDU id 100, channel 20 */
{20u, ..., (BapCanMsgId_t) BAP_Klima1_FSG_01, ...},
```

The BAP `BAP_CANUBS_TxData(channel, ...)` treats `channel in [20,30)` as
Ethernet and frames with the SoAd header before handing to the app TX bridge.

---

## 3.6 The interface channel ("20") and SoAd framing

The BAP stack is told the device is on **Ethernet** via the channel number
`20`. In `palb.c`:

```c
BAP_CANUBS_TxData(BapCanInterfaceChannel_t channel, ...)
{
    if (channel >= 20 && channel < 30) {
        // Ethernet: prepend SoAd header into palb_EthTxBuffers[index]
        palb_AddSoAdHdr(index, pduId, data, length);
        // then hand the whole SoAd frame to the app TX bridge
        BAP_Transmit_TxData(channel, pduId, palb_EthTxBuffers[index],
                            length + BAP_SOAD_HEADER_SIZE);
    }
}
```

The **SoAd header** (8 bytes) is what actually carries the message id + length
on the wire:

```
| Byte0-3: SoAd Message ID (big-endian) | Byte4-7: SoAd Length (big-endian) | user payload ... |
```

This header is:
- **added** on TX (`palb_AddSoAdHdr`, or directly in `FsgIpv6::transmitTxData`),
- **parsed/stripped** on RX (`BAP_RxIndication` reads the header, then feeds
  only the user bytes into the BCL ring buffer — see doc #4).

---

## 3.7 Retry logic — connecting is robust

`start()` does not assume the multicast came up on the first try:

```cpp
int32_t retry = 0;
while (!m_pduManager->isMulticastRunning()) {
    if (m_pduManager->startMulticast()) break;   // success
    retry++;
    Sleep(1000);                                 // retry every 1 second
}
```

`startMulticast()` → `socket_.start()` → `setupSocket()`. If the interface or
join is not ready yet, `start()` keeps retrying every second until the socket
is actually bound + joined and both threads are running (`running_ == true`).

---

## 3.8 Sequence diagram — connection

```
FSG (C++)                                    multicast bus           ASG-Client
  │                                               │                      │
  │ MulticastSocket::setupSocket()               │                      │
  │  recv sock bind :42514 + join ff14::1:fe     │                      │
  │  send sock bind :42993 hop255 on br0.3       │                      │
  │                                               │                      │
  │ recvLoop + sendLoop threads start            │                      │
  │ startMulticast() -> isMulticastRunning()=true│                      │
  │                                               │                      │
  │ BAP_Start → BAPConfig (msg 0x38000100) ─────►│────────────────────► ASG receives
  │ version info frame ─────────────────────────►│────────────────────►
  │ heartbeat 0x0A (fct4) every 1s ─────────────►│────────────────────► ASG keeps LSG Running
  │                                               │                      │
  │ (ASG reply frames 0x3000xxxx arrive) ◄────────│◄──────────────────── ASG sends
  │ recvLoop -> PDUParser -> PDUManager.onRecv    │                      │
```

*Document written from `FsgIpv6.cpp`, `PDUManager.cpp`, `MulticastSocket.cpp`,
`palb.c`, and `palb_cfg.c`.*
