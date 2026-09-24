# 5. How the WebSocket Works

This document explains the WebSocket layer of the simulation: what the browser
client sends, how the Node.js server receives and dispatches it, and how the
server pushes live status back to every browser.

The WebSocket is the **bridge between the browser UI and the Node.js wrapper.**
It is a *separate* channel from the IPv6 multicast bus (doc #3). The full chain
is:

```
Browser (React)  ──WebSocket :8080──►  Node.js wrapper  ──Named Pipe──►  C++ FSG ──multicast──► ASG
```

---

## 5.1 Ports & addresses

`runtime_fsg_simulation/src/common/common.ts`:

```ts
export const SERVER_IP = 'ws://10.134.197.32:8080';
export const FSG_SIMULATION_PORT = 8080;   // WebSocket server
export const FSG_HTTP_PORT = 8081;         // HTTP static server (serves the UI)
```

| Server           | Port   | Protocol  | Purpose                        |
|------------------|--------|-----------|--------------------------------|
| SocketHandler    | `8080` | WebSocket | real-time UI ↔ Node commands   |
| HttpRequestHandler | `8081` | HTTP      | serve index.html + bundle.js   |

---

## 5.2 Server side: `SocketHandler.ts` (port 8080)

The Node server uses the `ws` library. It starts a `WebSocketServer` and on
every incoming message **parses the JSON and forwards it to the manager**:

```ts
import { WebSocketServer, WebSocket } from 'ws';
import { FSG_SIMULATION_PORT } from '../../common/common.js';
import { globalFsgSimulationManager } from '../FsgSimulationManager.js';

export class SocketHandler {
    private m_wss: WebSocketServer;

    constructor() {
        this.m_wss = new WebSocketServer({ port: FSG_SIMULATION_PORT });   // :8080
    }

    public start() : void {
        this.m_wss.on('connection', (ws: WebSocket, request: IncomingMessage) => {
            console.log("new connection, client ip : ", request.socket.remoteAddress);

            ws.on('message', (data: any) => {
                // data is a JSON text frame from the browser
                const { targetId, payload } = JSON.parse(data.toString());
                globalFsgSimulationManager.handleHttpRequest(targetId, payload);
            });

            ws.on('close', (code, reason) => { /* ... */ });
        });
    }

    public stop(): void {
        this.m_wss.close();
    }

    /** Broadcast a payload string to ALL connected browsers. */
    public send(payload: string): void {
        this.m_wss.clients.forEach((client) => {
            if (client.readyState === WebSocket.OPEN) {
                client.send(payload);
            }
        });
    }
}
```

### The wire protocol

Every message between browser and Node server is a **JSON text frame** with
exactly two fields:

```json
{ "targetId": "<string topic>", "payload": [ ...values... ] }
```

- `targetId` — a string from `ComponentIndex_t` (e.g. `"MODIFY_HVAC_POWER_STATUS"`).
- `payload` — an array of values (numbers / booleans) associated with that topic.

---

## 5.3 Client side: `ClientSocketHandler.ts`

The browser connects and sets up handlers:

```ts
import { SERVER_IP } from "../../common/common.js";

class ClientSocketHandler {
    private m_socket!: WebSocket;

    constructor() {
        this.m_socket = new WebSocket(SERVER_IP);   // ws://10.134.197.32:8080
    }

    public start(): void {
        this.m_socket.onmessage = (event: MessageEvent) => {
            // server → browser push
            const response = JSON.parse(event.data.toString());
            globalClientRequestHandler.handleMessage(response);
        };
    }

    public sendRequest(payload: any): void {
        if (this.m_socket.readyState == WebSocket.OPEN) {
            this.m_socket.send(payload);   // browser → server
        }
    }
}
```

---

## 5.4 Client pub/sub: `ClientRequestHandler.ts`

The browser keeps a **topic → listener** map. This is the pub/sub used by every
React control:

```ts
class ClientRequestHandler {
    private m_listeners: Map<string, DataListener> = new Map();

    /** Receive a server push; spread the payload into the listener. */
    public handleMessage(response: any): void {
        const { targetId, payload } = response;
        const listener = this.m_listeners.get(targetId);
        if (listener) {
            if (Array.isArray(payload)) listener(...payload);   // spread
            else                       listener(payload);
        }
    }

    /** Send a request to the server. */
    public handleRequest(request_id: string, ...data: any[]): void {
        const data_json = { targetId: request_id, payload: data };
        globalClientSocketHandler.sendRequest(JSON.stringify(data_json));
    }

    /** Register a listener for a topic. */
    public subcribe(id: string, callback: DataListener): void {
        this.m_listeners.set(id, callback);
    }

    public unsubcribe(id: string): void {
        this.m_listeners.delete(id);
    }
}
```

---

## 5.5 Server dispatch: `FsgSimulationManager.handleHttpRequest`

On the Node side, `SocketHandler` hands each message to
`FsgSimulationManager.handleHttpRequest(targetId, payload)`. It does three
things:

1. **Swaps adjacent payload pairs** (a UI packing quirk):
   ```ts
   for (let i = 0; i < payload.length - 1; i += 2) {
       [payload[i], payload[i + 1]] = [payload[i + 1], payload[i]];
   }
   ```
2. **Switches on the string `targetId`** and calls the matching `_change*`
   method, packing the values into a byte payload whose first byte is a numeric
   opcode.
3. **Calls `m_simulationHandler.executeRequest(payload)`** — which writes the
   bytes into the Named Pipe for the C++ FSG (doc #6).

Example:

```ts
case ComponentIndex_t.MODIFY_HVAC_POWER_STATUS:
    this._changeHvacPowerStatus(payload[0]);
    break;
```

```ts
private _changeHvacPowerStatus(status: boolean): void {
    const payload = new Uint8Array(2);
    payload[0] = HttpRequest_t.MODIFY_HVAC_POWER_STATUS;   // 1
    payload[1] = +status;
    this.m_simulationHandler.executeRequest(payload);
}
```

---

## 5.6 Server → browser pushes (health check)

The Node server also *pushes* live state to all browsers. The most important
push is the **health check**, which tells the UI whether the C++ binary is
running:

```ts
private async _runHealthCheck(): Promise<void> {
    while (true) {
        const data_json = {
            targetId: ComponentIndex_t.HEALTH_CHECK_FSG_RUNNING,
            payload: this.m_simulationHandler.isBinaryRunning()
        };
        this.m_fsgSocketHandler.send(JSON.stringify(data_json));   // broadcast
        await sleep(3000);                                         // every 3 s
    }
}
```

`isBinaryRunning()`:

```ts
public isBinaryRunning(): boolean {
    return this.m_binaryProcess !== null && this.m_binaryProcess.pid !== undefined;
}
```

The browser's `HealthCheck` component subscribes to
`HEALTH_CHECK_FSG_RUNNING` and shows "System is Running / Stopped". The UI's
**ON/OFF** toggle sends `HEALTH_CHECK_FSG_RUNNING` with the inverse boolean; the
manager then spawns/stops the binary:

```ts
case ComponentIndex_t.HEALTH_CHECK_FSG_RUNNING:
    const binStatus: boolean = Boolean(payload[0]);
    if (binStatus)      this.m_simulationHandler.executeSimulationBinary();
    else                this.m_simulationHandler.stopSimulationBinary();
    break;
```

---

## 5.7 WebSocket sequence diagram

```
 Browser (React)                       Node.js wrapper
    │                                     │  SocketHandler :8080
    │  new WebSocket(ws://…:8080) ───────►│  'connection' event
    │                                     │
    │  JSON { targetId, payload }  ──────►│  ws 'message'
    │                                     │  → FsgSimulationManager.handleHttpRequest()
    │                                     │      swap pairs → _change* → executeRequest()
    │                                     │        └─► Named Pipe → C++ FSG
    │                                     │
    │  ◄──── JSON {targetId:HEALTH_CHECK, │  health-check broadcast every 3 s
    │         payload: isBinaryRunning()} │  (send() to all OPEN clients)
    │                                     │
    │  ◄──── JSON {targetId, payload}     │  (server can push any topic any time)
    │  onmessage → ClientRequestHandler.handleMessage → listener(...payload)
```

---

## 5.8 Topic names (`ComponentIndex_t`) vs numeric opcodes (`HttpRequest_t`)

Two enums exist — one on the **WebSocket** (string topic) and one on the
**pipe** (numeric opcode). They must agree by order:

`src/common/request_api.ts`:

```ts
// ComponentIndex_t — WebSocket topic strings
enum ComponentIndex_t {
  MODIFY_HVAC_POWER_STATUS, MODIFY_AC_COMPRESSOR_STATUS,
  MODIFY_AC_COMPRESSOR_ECO_MAX, MODIFY_HVAC_TEMP_ZL, MODIFY_HVAC_TEMP_ZR,
  MODIFY_HVAC_FAN_SPEED_ZL, MODIFY_HVAC_FAN_SPEED_ZR, MODIFY_RVC,
  MODIFY_TIRE_PRESSURE, MODIFY_SEAT_CLIMATE_ZL, MODIFY_SEAT_CLIMATE_ZR,
  MODIFY_AIR_CIRC_MANUAL, MODIFY_AIR_DIST_ZL, MODIFY_AIR_DIST_ZR,
  HEALTH_CHECK_FSG_RUNNING, ...
}

// HttpRequest_t — first byte of the pipe payload
enum HttpRequest_t {
  INVALID=0, MODIFY_HVAC_POWER_STATUS=1, MODIFY_AC_COMPRESSOR_STATUS=2,
  MODIFY_AC_COMPRESSOR_ECO_MAX=3, MODIFY_HVAC_TEMP_ZL=4, MODIFY_HVAC_TEMP_ZR=5,
  MODIFY_HVAC_FAN_SPEED_ZL=6, MODIFY_HVAC_FAN_SPEED_ZR=7, MODIFY_RVC=8,
  MODIFY_TIRE_PRESSURE=9, MODIFY_SEAT_CLIMATE_ZL=10, MODIFY_SEAT_CLIMATE_ZR=11,
  MODIFY_AIR_CIRC_MANUAL=12, MODIFY_AIR_DIST_ZL=13, MODIFY_AIR_DIST_ZR=14
}
```

The mapping from *WebSocket topic string* → *pipe opcode byte* is done inside
each `_change*` method (e.g. `MODIFY_HVAC_POWER_STATUS` → byte `1`).

---

## 5.9 HTTP static server (port 8081)

Separately, `HttpRequestHandler.ts` (Node) serves the UI on port 8081:

```ts
// serves index.html and dist/client/bundle.js (esbuild React bundle)
// JS files are sent with Content-Type text/javascript
```

The browser loads the React page from `http://host:8081`, then opens the
WebSocket to `ws://host:8080`. The two ports cooperate: 8081 gives you the app,
8080 gives you real-time data.

*Document written from `SocketHandler.ts`, `ClientSocketHandler.ts`,
`ClientRequestHandler.ts`, `FsgSimulationManager.ts`, and `common.ts`.*
