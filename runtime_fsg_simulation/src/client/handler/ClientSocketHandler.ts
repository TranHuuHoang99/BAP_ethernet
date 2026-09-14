import { WebSocket } from "ws";
import { SERVER_IP } from "../common.js";
import { spec } from "node:test/reporters";

type DataListener = (data: any) => void;

class ClientSocketHandler {
    private m_socket!: WebSocket;
    private m_listeners: Map<string, DataListener> = new Map();

    constructor() {
        this.m_socket = new WebSocket(SERVER_IP);
    }

    public start(): void {
        this.m_socket.onmessage = (event: WebSocket.MessageEvent) => {
            console.log("Received data from server: ", event.data);
            // JSON: { "targetId": "div_99", "payload": "Hello World" }
            try {
                const response = JSON.parse(event.data.toString());
                const {targetId, payload} = response;
                const specific_listener = this.m_listeners.get(targetId);
                if (specific_listener) {
                    specific_listener(payload);
                }
            } catch (err) {
                console.error("Server sent wrong format of data")
            }
        };
    }

    public sendRequest(payload: any): void {
        if (this.m_socket.readyState == WebSocket.OPEN) {
            console.log("send request");
            this.m_socket.send(payload);
        } else {
            console.log("socket is not ready");
        }
    }

    public subcribe(id: string, callback: DataListener): void {
        this.m_listeners.set(id, callback);
    }

    public unsubcribe(id: string): void {
        this.m_listeners.delete(id);
    }
}

export const globalSocketHandler: ClientSocketHandler = new ClientSocketHandler();
