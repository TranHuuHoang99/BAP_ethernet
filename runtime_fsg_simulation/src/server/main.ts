import { Socket } from "node:dgram";
import { SocketHandler } from "./handler/SocketHandler.js";
import { HttpRequestHandler } from "./handler/HttpRequestHandler.js";
import { error } from "node:console";

async function main(): Promise<void> {
    console.log("start fsg simulation server");
    const m_socketHandler: SocketHandler = new SocketHandler();
    const m_httpRequestHandler: HttpRequestHandler = new HttpRequestHandler();
    m_socketHandler?.start();
    m_httpRequestHandler?.start();
}

main().catch((error) => {
    console.error("Error occured : ", error);
    process.exit(1);
})
