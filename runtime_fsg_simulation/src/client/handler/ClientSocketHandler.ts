import { SERVER_IP } from "../../common/common.js";
import { globalClientRequestHandler } from "./ClientRequestHandler.js";

class ClientSocketHandler {
    private m_socket!: WebSocket;

    constructor() {
        this.m_socket = new WebSocket(SERVER_IP);
    }

    public start(): void {
        this.m_socket.onmessage = (event: MessageEvent) => {
            console.log("Received data from server: ", event.data);
            // JSON: { "targetId": "div_99", "payload": "Hello World" }
            try {
                const response = JSON.parse(event.data.toString());
                globalClientRequestHandler.handleMessage(response);
            } catch (err) {
                console.error("Server sent wrong format of data");
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

}

export const globalClientSocketHandler: ClientSocketHandler = new ClientSocketHandler();
