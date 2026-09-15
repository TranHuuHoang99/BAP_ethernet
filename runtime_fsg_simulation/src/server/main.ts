import { globalFsgSimulationManager } from "./FsgSimulationManager.js";

async function main(): Promise<void> {
    console.log("start fsg simulation server");
    globalFsgSimulationManager?.start();
}

main().catch((error) => {
    console.error("Error occured : ", error);
    globalFsgSimulationManager?.stop();
    process.exit(1);
})
