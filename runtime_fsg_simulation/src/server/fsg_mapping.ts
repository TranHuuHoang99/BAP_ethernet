import { REQUEST_HVAC_POWER } from "../common/request_api.js";
import { globalFsgSimulationManager } from "./FsgSimulationManager.js";

globalFsgSimulationManager
type RequestListener_t = (...data: any[]) => void;
export const FsgRequestMapping: Map<string, RequestListener_t> = new Map([
    [REQUEST_HVAC_POWER, (...data: any[]) => globalFsgSimulationManager.handleHvacPowerRequest(data[0])]
]);