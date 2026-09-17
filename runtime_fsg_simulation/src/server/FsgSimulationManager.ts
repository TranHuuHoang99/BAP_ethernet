import { ComponentIndex_t, HttpRequest_t } from "../common/request_api.js";
import { HttpRequestHandler } from "./handler/HttpRequestHandler.js";
import { SimulationHandler } from "./handler/SimulationHandler.js";
import { SocketHandler } from "./handler/SocketHandler.js";

class FsgSimulationManager {
    private m_fsgSocketHandler: SocketHandler = new SocketHandler();
    private m_httpRequestHandler: HttpRequestHandler = new HttpRequestHandler();
    private m_simulationHandler: SimulationHandler = new SimulationHandler();

    constructor()
    {
    }

    private async _runHealthCheck(): Promise<void> {
        const sleep = (ms: number) => new Promise(resolve => setTimeout(resolve, ms));
        while (true) {
            const data_json = {
                targetId: ComponentIndex_t.HEALTH_CHECK_FSG_RUNNING,
                payload: this.m_simulationHandler.isBinaryRunning()
            };

            this.m_fsgSocketHandler.send(JSON.stringify(data_json)); 

            await sleep(3000);
        }
    }

    public start(): void
    {
        this.m_fsgSocketHandler?.start();
        this.m_httpRequestHandler?.start();
        this._runHealthCheck();
    }

    public stop(): void
    {
        this.m_fsgSocketHandler.stop();
    }

    public handleHttpRequest(request_t: any, payload: any[]): void
    {
        switch (request_t) {
            case ComponentIndex_t.MODIFY_HVAC_POWER_STATUS:
            {
                this._changeHvacPowerStatus(payload[0]);
                break;
            }
            case ComponentIndex_t.MODIFY_AC_COMPRESSOR_STATUS:
            {
                if (payload.length < 3) {
                    console.error("Ac compressor status payload length error");
                    break;
                }
                this._changeAcCompressorStatus(payload[0], payload[1], payload[2]);
                break;
            }
            case ComponentIndex_t.MODIFY_AC_COMPRESSOR_ECO_MAX:
            {
                if (payload.length < 3) {
                    console.error("Ac compressor eco max payload length error");
                    break;
                }
                this._changeAcCompressorEcoMax(payload[0], payload[1], payload[2]);
                break;
            }
            case ComponentIndex_t.MODIFY_HVAC_TEMP_ZL:
            {
                if (payload.length < 4) {
                    console.error("HVAC ZL temperature payload length error");
                    break;
                }
                this._changeTemperatureZL(payload[0], payload[1], payload[2], payload[3]);
                break;
            }
            case ComponentIndex_t.MODIFY_HVAC_TEMP_ZR:
            {
                if (payload.length < 4) {
                    console.error("HVAC ZL temperature payload length error");
                    break;
                }
                this._changeTemperatureZR(payload[0], payload[1], payload[2], payload[3]);
                break;
            }
            case ComponentIndex_t.MODIFY_HVAC_FAN_SPEED_ZL:
            {
                if (payload.length < 3) {
                    console.error("HVAC fan speed ZL payload length error");
                    break;
                }
                this._changeFanSpeedZL(payload[0], payload[1], payload[2]);
                break;
            }
            case ComponentIndex_t.MODIFY_HVAC_FAN_SPEED_ZR:
            {
                if (payload.length < 3) {
                    console.error("HVAC fan speed ZR payload length error");
                    break;
                }
                this._changeFanSpeedZR(payload[0], payload[1], payload[2]);
                break;
            }
            case ComponentIndex_t.MODIFY_RVC:
            {
                if (payload.length < 1) {
                    console.error("RVC view payload length error");
                    break;
                }
                this._changeRvc(payload[0]);
                break;
            }
            case ComponentIndex_t.MODIFY_TIRE_PRESSURE:
            {
                break;
            }
            case ComponentIndex_t.MODIFY_SEAT_CLIMATE_ZL:
            {
                if (payload.length < 4) {
                    console.error("SEAT climate ZL payload length error");
                    break;
                }
                this._changeSeatClimateZL(payload[0], payload[1], payload[2], payload[3]);
                break;
            }
            case ComponentIndex_t.MODIFY_SEAT_CLIMATE_ZR:
            {
                if (payload.length < 4) {
                    console.error("SEAT climate ZR payload length error");
                    break;
                }
                this._changeSeatClimateZR(payload[0], payload[1], payload[2], payload[3]);
                break;
            }
            case ComponentIndex_t.MODIFY_AIR_CIRC_MANUAL:
            {
                if (payload.length < 1) {
                    console.error("air circulation manual payload length error");
                    break;
                }
                this._changeAirCirculationManual(payload[0]);
                break;
            }
            case ComponentIndex_t.MODIFY_AIR_DIST_ZL:
            {
                if (payload.length < 1) {
                    console.error("air distribution ZL payload length error");
                    break;
                }
                this._changeAirDistributionZL(payload[0]);
                break;
            }
            case ComponentIndex_t.MODIFY_AIR_DIST_ZR:
            {
                if (payload.length < 1) {
                    console.error("air distribution ZR payload length error");
                    break;
                }
                this._changeAirDistributionZR(payload[0]);
                break;
            }
            case ComponentIndex_t.HEALTH_CHECK_FSG_RUNNING:
            {
                console.log("hoangprodn, payload : ", payload);
                if (payload.length < 1) {
                    console.error("request execute binary comand is empty");
                    break;
                }
                const binStatus: boolean = Boolean(payload[0]);
                console.log("bin : ", binStatus);
                if (binStatus) {
                    console.log("receive execute binary request from client");
                    this.m_simulationHandler.executeSimulationBinary();
                } else {
                    this.m_simulationHandler.stopSimulationBinary();
                }
                break;
            }
            default:
            {
                console.warn("Current request is not supported : ", request_t);
                break;
            }
        }
    }

    private _changeHvacPowerStatus(status: boolean): void
    {
        const payload = new Uint8Array(2);
        payload[0] = HttpRequest_t.MODIFY_HVAC_POWER_STATUS;
        payload[1] = +status;
        console.log("HVAC power status hex : ", payload);
        this.m_simulationHandler.executeRequest(payload);
    }

    private _changeAcCompressorStatus(status: boolean,
                                      modi_state: boolean,
                                      modi_reason: number) : void
    {
        const payload = new Uint8Array(4);
        payload[0] = HttpRequest_t.MODIFY_AC_COMPRESSOR_STATUS;
        payload[1] = +status;
        payload[2] = +modi_state;
        payload[3] = modi_reason;
        console.log("AC compressor status hex : ", payload);
        this.m_simulationHandler.executeRequest(payload);
    }

    private _changeAcCompressorEcoMax(option: boolean,
                                      modi_state: boolean,
                                      modi_reason: number) : void
    {
        const payload = new Uint8Array(4);
        payload[0] = HttpRequest_t.MODIFY_AC_COMPRESSOR_ECO_MAX;
        payload[1] = +option;
        payload[2] = +modi_state;
        payload[3] = modi_reason;
        console.log("ac compress eco max : ", payload);
        this.m_simulationHandler.executeRequest(payload);
    }

    private _changeTemperatureZL(value: number,
                                 unit: number,
                                 modi_state: boolean,
                                 modi_reason: number) : void
    {
        const buffer = new ArrayBuffer(8);
        const view = new DataView(buffer);
        // little endian because of window architecture
        view.setFloat32(1, value, true);
        view.setUint8(5, unit);
        view.setUint8(6, modi_state ? 1 : 0);
        view.setUint8(7, modi_reason);
        const payload = new Uint8Array(buffer);
        payload[0] = HttpRequest_t.MODIFY_HVAC_TEMP_ZL;
        console.log("change left zone temperature : ", payload);
        this.m_simulationHandler.executeRequest(payload);
    }

    private _changeTemperatureZR(value: number,
                                 unit: number,
                                 modi_state: boolean,
                                 modi_reason: number) : void
    {
        const buffer = new ArrayBuffer(8);
        const view = new DataView(buffer);
        // little endian because of window architecture
        view.setFloat32(1, value, true);
        view.setUint8(5, unit);
        view.setUint8(6, modi_state ? 1 : 0);
        view.setUint8(7, modi_reason);
        const payload = new Uint8Array(buffer);
        payload[0] = HttpRequest_t.MODIFY_HVAC_TEMP_ZR;
        console.log("change right zone temperature : ", payload);
        this.m_simulationHandler.executeRequest(payload);
    }

    private _changeFanSpeedZL(value: number,
                              modi_state: boolean,
                              modi_reason: number) : void
    {
        const payload = new Uint8Array(4);
        payload[0] = HttpRequest_t.MODIFY_HVAC_FAN_SPEED_ZL;
        payload[1] = value;
        payload[2] = +modi_state;
        payload[3] = modi_reason;
        console.log("fan speed zl : ", payload);
        this.m_simulationHandler.executeRequest(payload);
    }

    private _changeFanSpeedZR(value: number,
                              modi_state: boolean,
                              modi_reason: number) : void
    {
        const payload = new Uint8Array(4);
        payload[0] = HttpRequest_t.MODIFY_HVAC_FAN_SPEED_ZR;
        payload[1] = value;
        payload[2] = +modi_state;
        payload[3] = modi_reason;
        console.log("fan speed zr : ", payload);
        this.m_simulationHandler.executeRequest(payload);
    }

    private _changeRvc(status: boolean): void
    {

    }

    private _changeSeatClimateZL(heat_val: number,
                                 heat_state: number,
                                 ventilation_val: number,
                                 ventilation_state: number) : void
    {
        const payload = new Uint8Array(5);
        payload[0] = HttpRequest_t.MODIFY_SEAT_CLIMATE_ZL;
        payload[1] = heat_val;
        payload[2] = heat_state;
        payload[3] = ventilation_val;
        payload[4] = ventilation_state;
        console.log("seat climate zl : ", payload);
        this.m_simulationHandler.executeRequest(payload);
    }

    private _changeSeatClimateZR(heat_val: number,
                                 heat_state: number,
                                 ventilation_val: number,
                                 ventilation_state: number) : void
    {
        const payload = new Uint8Array(5);
        payload[0] = HttpRequest_t.MODIFY_SEAT_CLIMATE_ZR;
        payload[1] = heat_val;
        payload[2] = heat_state;
        payload[3] = ventilation_val;
        payload[4] = ventilation_state;
        console.log("seat climate zl : ", payload);
        this.m_simulationHandler.executeRequest(payload);
    }

    private _changeAirCirculationManual(status: boolean): void
    {
        const payload = new Uint8Array(2);
        payload[0] = HttpRequest_t.MODIFY_AIR_CIRC_MANUAL;
        payload[1] = +status;
        console.log("air circulation manual : ", payload);
        this.m_simulationHandler.executeRequest(payload);
    }

    private _changeAirDistributionZL(val: number): void
    {
        const payload = new Uint8Array(2);
        payload[0] = HttpRequest_t.MODIFY_AIR_DIST_ZL;
        payload[1] = val
        console.log("air distribution zl : ", payload);
        this.m_simulationHandler.executeRequest(payload);
    }

    private _changeAirDistributionZR(val: number): void
    {
        const payload = new Uint8Array(2);
        payload[0] = HttpRequest_t.MODIFY_AIR_DIST_ZR;
        payload[1] = val
        console.log("air distribution zr : ", payload);
        this.m_simulationHandler.executeRequest(payload);
    }
}

export const globalFsgSimulationManager: FsgSimulationManager = new FsgSimulationManager();
