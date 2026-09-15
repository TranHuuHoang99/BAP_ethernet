import { globalClientSocketHandler } from "./ClientSocketHandler.js";

type DataListener = (...data: any[]) => void;

class ClientRequestHandler {
    private m_listeners: Map<string, DataListener> = new Map();

    constructor() {

    }

    public handleMessage(response: any): void {
        const {targetId, payload} = response;
        const specific_listener = this.m_listeners.get(targetId);
        if (specific_listener) {
            if (Array.isArray(payload)) {
                specific_listener(...payload);
            } else {
                specific_listener(payload);
            }
        }
    }

    public handleRequest(request_id: string, ...data: any[]): void {
        const data_json = {
            targetId: request_id,
            payload: data
        };
        globalClientSocketHandler.sendRequest(JSON.stringify(data_json));
    }

    public subcribe(id: string, callback: DataListener): void {
        this.m_listeners.set(id, callback);
    }

    public unsubcribe(id: string): void {
        this.m_listeners.delete(id);
    }
}

export const globalClientRequestHandler: ClientRequestHandler = new ClientRequestHandler();
