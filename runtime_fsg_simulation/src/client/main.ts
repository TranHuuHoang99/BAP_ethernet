import { globalClientSocketHandler } from "./handler/ClientSocketHandler.js";
import "./handler/ClientViewHandler.js";

async function main(): Promise<void> {
    console.log("start client");
    globalClientSocketHandler.start();
}

main().catch((error) => {
    console.error("Error occured: ", error);
    process.exit(1);
});
