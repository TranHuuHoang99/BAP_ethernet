# 1. How FSG Creates Its Buffers

This document explains, end-to-end, how the FSG allocates and initializes the
send buffers for every function (fct) it hosts. The answer has **two layers**:

1. A **design-time / compile-time** layer — the `fsg.xml` configuration is
   turned into ROM tables (`BAP_FctRomTables`, `BCL_TxBuffer*`) by the BAPgen
   code generator.
2. A **run-time** layer — the C++ server walks those tables and calls the BAP
   API to actually allocate + seed each send buffer.

---

## 1.1 The design-time source: `fsg.xml`

`FSG/FsgLarge/fsg.xml` is the master configuration. It declares the project as
a *Large FSG* with a 10 ms task cycle:

```xml
<Config SGType="LargeFSG" TaskTimeMs="10" .../>
```

It then declares, for every LSG, its **functions** and for each function:

- its **function id** (`fctId`),
- its **data type** (`BapDt_Int8/16/32`, `ByteSequence`, `FixedByteSequence`, `Void`),
- its **TX size** (`u32TxSize` — number of payload bytes FSG → ASG),
- its **function class** (`Property`, `Method`, `Cache`).

Example excerpt — the ClimateZone LSG (`FLsg id="1"`), function `GetAll`
(`fctId="1"`) is a **Cache** of a 214-byte ByteSequence:

```xml
<FLsg id="1">
  <Fct id="1" Name="GetAll" Class="Cache" SgClass="FSG"
       TxType="ByteSequence" TxLength="214" CanSegInterface="ChannelOneTwoThreeFour"/>
  ...
</FLsg>
```

`BAP_Config` (fctId 2) is a `FixedByteSequence` (6 bytes), `FunctionList`
(fctId 3) is a ByteSequence (8 bytes), `HeartBeat` (fctId 4) is a Uint8. These
three are the **protocol-required** functions that every FSG must carry.

---

## 1.2 What BAPgen generates (`fsg.c`)

Running BAPgen 1.12.2 on `fsg.xml` produces (among others) `FSG/FsgLarge/fsg.c`
(7467 lines). The key generated tables are:

### `BAP_FctRomTables[]` — one row per function

```c
BapFctRomRow_ot BAP_FctRomTables[BAP_FCT_ROM_TABLE_ROWS] =
{
  { /* LSG#id="1", Function#id="1"  */
    BapFctCls_Cache,            /* eFunctionClass */
    (fctId_t)0x01,              /* fctId */
    (lsgId_t)0x01,              /* lsgId */
    BapDt_ByteSequence,         /* eTxDataType */
    214u,                       /* u32TxSize */
    ...
  },
  ...
};
```

Each row describes: function class, id, owning LSG, TX data type, and TX size.
It also carries the **link to a BCL TX buffer** for this function (via the
`BCL_TxBuffer*` entry referenced from the associated `BAP_CanLsgInitData` /
`BCL_TxBuffer` mapping rows).

### `BAP_LsgRomTables[]` — one row per LSG

```c
BapLsgRomRow_ot BAP_LsgRomTables[BAP_LSG_ROM_TABLE_ROWS] =
{
  /* LSG#id="1" (ClimateZone) */
  {
    (lsgId_t)0x01,
    ...,
    0u,          /* u16FctRomIndex: start index into BAP_FctRomTables */
    51u,         /* u8FctRomTableSize: number of functions this LSG owns */
    ...
  },
  ...
};
```

- `u16FctRomIndex` — where this LSG's functions begin in `BAP_FctRomTables`.
- `u8FctRomTableSize` — how many consecutive rows belong to this LSG.

### `BCL_TxBuffer0 … BCL_TxBuffer42` — the actual byte buffers

`fsg.c` also allocates a **BCL send buffer per function**, e.g.:

```c
static uint8_t BCL_TxBuffer0[  BAP_MIN_PDU_SIZE];
static uint8_t BCL_TxBuffer1[  BAP_MIN_PDU_SIZE];
...
```

and a mapping table that binds each `(lsgId, fctId)` to its buffer plus the
message id to transmit on:

```c
{20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer4, 0u,
 (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[4], 1},
```

Here `20u` is the **Ethernet interface channel**, `BAP_Klima1_FSG_01` is the
FSG→ASG message id for ClimateZone, and `&BAP_FctRomTables[4]` links back to
the function's ROM row. This is how the BAP stack knows: *"function 13 of LSG 1
lives in BCL_TxBuffer4 and is transmitted with message id 0x38000100"*.

---

## 1.3 The run-time init: `FsgIpv6::_initLsg()`

At startup, `main.cpp` calls `FsgIpv6::instance()->init()`. Inside `init()`,
`_initLsg()` runs for every LSG in `lsgId_vec`:

```cpp
int32_t FsgIpv6::_initLsg(void)
{
    for (const lsgId_t lsg : lsgId_vec) {
        // 1) init LSG in the BAP stack
        if (BAP_Init(lsg) != BapError_t::BapErr_OK) { ... return -1; }

        // 2) allocate + seed the send buffers for every function of this LSG
        if (_initAllSendBuffers(lsg) != 0) { ... return -1; }
    }
    return 0;
}
```

### Step 1 — `BAP_Init(lsg)` (inside `bap_bal.c`)

`BAP_Init` → `BAP_BAL_Init(FALSE, lsgId)`. It:

1. Looks up the LSG ROM row via `BAP_GetLsgRomRow`.
2. Calls `BAP_BPL_Init()` (Protocol Layer init).
3. For an **FSG**, copies the ROM defaults for `FunctionList` and `BAPConfig`
   into the LSG's RAM row.
4. Calls `BAP_BAL_InitFSGBuffers()` — this fills the internal function id in
   each BCL send buffer so the stack knows which buffer belongs to which fctId.
5. Sets the LSG state to `BapLayerLsgStat_Initialized`.

After this call the LSG is *initialized* but its send buffers are not yet
seeded with values — that is exactly what step 2 does.

### Step 2 — `_initAllSendBuffers(lsgId)`

This is the **core buffer-creation loop**. It reads the LSG's ROM row, walks
every function row in its range of `BAP_FctRomTables`, and initializes the send
buffer for the functions that need one.

```cpp
int32_t FsgIpv6::_initAllSendBuffers(const lsgId_t aLsgId)
{
    BapLsgRomRow_pot lsgRomRow = BAP_GetLsgRomRow(aLsgId);
    const int32_t fct_numb  = lsgRomRow->u8FctRomTableSize;   // how many fcts
    const int32_t fct_index = lsgRomRow->u16FctRomIndex;      // where they start

    for (int32_t i = 0; i < fct_numb; i++) {
        const BapFctRomRow_ot& fct = BAP_FctRomTables[fct_index + i];

        // ---- SKIP functions that need no send buffer ----
        if (fct.eFunctionClass == BapFctCls_Method
            || fct.eFunctionClass == BapFctCls_Cache
            || fct.fctId == (fctId_t)2    // BAP_Config
            || fct.fctId == (fctId_t)3    // FunctionList
            || fct.fctId == (fctId_t)4    // HeartBeat
            ) { continue; }

        if (fct.eTxDataType == BapDataType_t::BapDt_Void) { continue; }

        // ---- Create + seed the send buffer, by data type ----
        switch (fct.eTxDataType) {
            case BapDataType_t::BapDt_Int8:
                err = BAP_InitSendBufferInt8(aLsgId, fct.fctId, (uint8_t)0u);
                break;
            case BapDataType_t::BapDt_Int16:
                err = BAP_InitSendBufferInt16(aLsgId, fct.fctId, (uint16_t)0u);
                break;
            case BapDataType_t::BapDt_Int32:
                err = BAP_InitSendBufferInt32(aLsgId, fct.fctId, (uint32_t)0u);
                break;
            case BapDataType_t::BapDt_FixedByteSequence: // FALL-THROUGH
            case BapDataType_t::BapDt_ByteSequence:
            {
                std::vector<uint8_t> zeroBuf(fct.u32TxSize, 0u);
                err = BAP_InitSendBufferByteSequence(aLsgId, fct.fctId,
                                                     zeroBuf.data(),
                                                     fct.u32TxSize);
                break;
            }
            default: /* unknown type -> warn & skip */ break;
        }
    }
    return (firstErr == BapError_t::BapErr_OK) ? 0 : -1;
}
```

### Which functions are skipped, and why

| Skip condition                      | Reason                                                                 |
|-------------------------------------|------------------------------------------------------------------------|
| `eFunctionClass == Method`          | A method is a command FSG→ASG, not a data attribute to buffer.          |
| `eFunctionClass == Cache`           | `GetAll` (Cache) collects *all* values on demand; it has no own buffer. |
| `fctId == 2` (BAP_Config)           | Written on `BAP_Start` by the stack, not by the app.                    |
| `fctId == 3` (FunctionList)         | Holds the static function list, filled at `BAP_Init`.                   |
| `fctId == 4` (HeartBeat)            | Sent by the heartbeat dispatcher, not a data buffer.                    |
| `eTxDataType == Void`               | No payload → nothing to buffer.                                         |

### What each `BAP_InitSendBuffer*` call does

`BAP_InitSendBufferInt8/16/32/ByteSequence` (in `bap_bal.c`) validate the
request and then call `BAP_BPL_BufferSet()`, which writes the initial value
into the BCL TX buffer bound to that `(lsgId, fctId)` in the generated tables.

**The seed values:**

| TX data type        | BAP call                                      | Seed value             |
|---------------------|-----------------------------------------------|------------------------|
| `BapDt_Int8`        | `BAP_InitSendBufferInt8(lsg, fct, 0)`         | `0x00`                 |
| `BapDt_Int16`       | `BAP_InitSendBufferInt16(lsg, fct, 0)`        | `0x0000`               |
| `BapDt_Int32`       | `BAP_InitSendBufferInt32(lsg, fct, 0)`        | `0x00000000`           |
| `ByteSequence` / `FixedByteSequence` | `BAP_InitSendBufferByteSequence(lsg, fct, zeroBuf, u32TxSize)` | `0x00…00` (u32TxSize zero bytes) |

> **Takeaway:** after `_initAllSendBuffers`, every *data* function of every LSG
> has a valid, zero-initialized BCL TX buffer. It becomes non-zero later when
> the UI commands flow through `BapParser` → `write_*` → `BAP_Request*` (see
> doc #6).

---

## 1.4 The parallel in-memory mirror: the `DataBase`

`start()` also builds an identical logical mirror called `DataBase`
(`_genDataBase()` → `_genDataFollowLsgId()`). It uses the **same skip rules**
and the **same type switch**, but instead of touching the BAP stack it fills a
C++ map so the application can read/write values without going through BAP:

```cpp
// FsgDataBase.hpp
struct DataBase {
    std::map<lsgId_t, std::map<fctId_t, std::any>> database;
    // template insert<uint8_t/16/32/vector<uint8_t>>(lsg, fct, {data, len})
    // template loadData<...>(lsg, fct) -> std::pair<data, len>
    // template storeData<...>(lsg, fct, {data, len})
    std::mutex mt_loader;   // guards concurrent query/update
};
```

```cpp
// _genDataFollowLsgId(): same skip + switch as above, e.g.
case BapDataType_t::BapDt_Int8:
    err = m_dataBase->insert<uint8_t>(lsgId, fct.fctId, {0u, fct.u32TxSize});
    break;
case BapDataType_t::BapDt_ByteSequence:
    std::vector<uint8_t> zeroBuf(fct.u32TxSize, 0u);
    err = m_dataBase->insert<std::vector<uint8_t>>(lsgId, fct.fctId,
                                                   {zeroBuf, fct.u32TxSize});
    break;
```

So there are **two parallel "buffers"**:

- the **BAP BCL TX buffers** (inside the stack, used when sending on the bus),
- the **`DataBase` map** (inside the C++ app, used by the parser for
  encode/decode).

They are kept in sync by `BapParser` (doc #6): every UI command updates the
`DataBase` via `storeData`, then pushes the value into the BAP stack via
`write_*` → `BAP_Request*`.

---

## 1.5 Summary diagram

```
 fsg.xml ──► BAPgen ──► fsg.c
                          ├── BAP_FctRomTables[]    (per function: class, type, size)
                          ├── BAP_LsgRomTables[]    (per LSG: index+count)
                          └── BCL_TxBuffer0..42     (per function: raw byte buffer)
                                      │
        main() ──► FsgIpv6::init() ────┤
                          ├── BAP_Init(lsg)         → LSG = Initialized
                          │      └─ BAP_BAL_InitFSGBuffers() (bind fctId→buffer)
                          └── _initAllSendBuffers(lsg)
                                  └─ for each data fct (skip Method/Cache/2/3/4/Void)
                                        BAP_InitSendBuffer{Int8,Int16,Int32,ByteSequence}(...)
                                        → writes seed (0) into BCL Tx buffer
        start() ──► _genDataBase()     (same loop → fills DataBase map)
```
