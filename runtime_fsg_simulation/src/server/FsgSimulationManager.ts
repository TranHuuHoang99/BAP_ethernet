import { HttpRequestHandler } from "./handler/HttpRequestHandler.js";
import { SocketHandler } from "./handler/SocketHandler.js";

class FsgSimulationManager {
    private m_fsgSocketHandler: SocketHandler = new SocketHandler();
    private m_httpRequestHandler: HttpRequestHandler = new HttpRequestHandler();

    constructor() {
        
    }

    public start(): void {
        this.m_fsgSocketHandler?.start();
        this.m_httpRequestHandler?.start();
    }

    public stop(): void {
        this.m_fsgSocketHandler.stop();
    }

    public handleHvacPowerRequest(hvacSetStatus: boolean): void {
        // do some logic here
        console.log("request set HVAC to : ", hvacSetStatus);
    }
}

export const globalFsgSimulationManager: FsgSimulationManager = new FsgSimulationManager();
