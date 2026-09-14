import { WebSocketServer, WebSocket, type RawData } from 'ws';
import { FSG_SIMULATION_PORT } from '../config/ethernet.js';
import type { IncomingMessage } from 'node:http';

export class SocketHandler {
    private m_wss: WebSocketServer;
    constructor() {
        this.m_wss = new WebSocketServer({port : FSG_SIMULATION_PORT});
    }

    public start() : void {
        this.m_wss.on('connection', (ws: WebSocket, request: IncomingMessage) => {
            console.log("new connection, client ip : ", request.socket.remoteAddress);
            ws.send("hello world!!!");

            ws.on('message', (data: Buffer | string | ArrayBuffer) => {
                console.log("received requests from client : ", request.socket.remoteAddress);
                const requestType: string = data.toString();
                if (requestType == 'GET_DATA') {
                    ws.send("hoangprodn123456 hello world");
                }
            });

            ws.on('close', (code: number, reason: Buffer) => {
                
            });
        });
    }

    public send(payload: any[]): void {

    }
}

