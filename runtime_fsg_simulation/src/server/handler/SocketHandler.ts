import { WebSocketServer, WebSocket, type RawData } from 'ws';
import type { IncomingMessage } from 'node:http';
import { FSG_SIMULATION_PORT } from '../../common/common.js';
import { FsgRequestMapping } from '../fsg_mapping.js';

export class SocketHandler {
    private m_wss: WebSocketServer;

    constructor() {
        this.m_wss = new WebSocketServer({port : FSG_SIMULATION_PORT});
    }

    public start() : void {
        this.m_wss.on('connection', (ws: WebSocket, request: IncomingMessage) => {
            console.log("new connection, client ip : ", request.socket.remoteAddress);
            ws.send("hello world!!!");

            ws.on('message', (data: any) => {
                console.log("received requests from client : ", request.socket.remoteAddress);
                try {
                    const { targetId, payload } = JSON.parse(data.toString());
                    const request_listener = FsgRequestMapping.get(targetId);
                    if (request_listener) {
                        if (Array.isArray(payload)) {
                            request_listener(...payload);
                        } else {
                            request_listener(payload);
                        }
                    }
                } catch (err) {
                    console.error("client request wrong format of data");
                }
            });

            ws.on('close', (code: number, reason: Buffer) => {
                
            });
        });
    }

    public stop(): void {
        this.m_wss.close();
    }

    public send(...payload: any[]): void {

    }
}

