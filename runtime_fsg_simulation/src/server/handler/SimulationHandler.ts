import { spawn, type ChildProcess } from 'child_process';
import * as fs from 'fs'
import path from 'path';

const PIPE_NAME = '\\\\.\\pipe\\MyTerminalPipe';
const BINARY_PATH = path.join(process.cwd(),
                              'simulation_executable_file',
                              'fsg_ipv6_multicast.exe');
export class SimulationHandler {
    private m_binaryProcess: ChildProcess | null = null;
    private m_isIntentionalStop: boolean = false;

    constructor()
    {
        // this.executeSimulationBinary();
    }

    public executeSimulationBinary(): void {
        console.log(`Starting binary process from: ${BINARY_PATH}`);
        this.m_isIntentionalStop = false;

        this.m_binaryProcess = spawn(BINARY_PATH, [], {
            stdio: 'pipe',
            windowsHide: true
        });

        this.m_binaryProcess.stdout?.on('data', (data) => {
            console.log(`[Binary Stdout]: ${data.toString().trim()}`);
        });

        this.m_binaryProcess.stderr?.on('data', (data) => {
            console.error(`[Binary Stderr]: ${data.toString().trim()}`);
        });

        this.m_binaryProcess.on('close', (code, signal) => {
            console.warn(`Binary process exited with code ${code} and signal ${signal}`);
            this.m_binaryProcess = null;

            if (!this.m_isIntentionalStop) {
                console.log("Binary crashed or closed unexpectedly! Re-spawning in 3 seconds...");
                setTimeout(() => {
                    this.executeSimulationBinary();
                }, 3000);
            }
        });

        this.m_binaryProcess.on('error', (err) => {
            console.error("Failed to start binary process:", err);
        });
    }

    public isBinaryRunning(): boolean {
        return this.m_binaryProcess !== null && this.m_binaryProcess.pid !== undefined;
    }

    public stopSimulationBinary(): void {
        if (this.m_binaryProcess) {
            console.log("Intentionally stopping the binary process...");
            this.m_isIntentionalStop = true;
            this.m_binaryProcess.kill();
            this.m_binaryProcess = null;
        }
    }

    public executeRequest(payload: Uint8Array): void
    {
        console.log("execute request from client websocket");
        fs.open(PIPE_NAME, 'w', (err, fd) => {
            if (err) {
                console.error("Can not connect to pipe : ", PIPE_NAME);
                console.error("Error detailed : ", err);
                return;
            }
            fs.write(fd, payload, 0, payload.length, null, (writeErr) => {
                if (writeErr) {
                    console.error("Failed to push data to pipe", writeErr);
                } else {
                    console.log("Success to push data to pipe");
                }
                fs.close(fd, () => {});
            });
        });
    }

    public onListenPIPE(): void
    {
        console.log("listen on pipe, ", PIPE_NAME);
        const stream = fs.createReadStream(PIPE_NAME);

        stream.on('data', (chunk: Buffer) => {
            console.log("Receive data from pipe !!!", chunk);
        });

        stream.on('error', (err) => {
            console.error("Pipe system error, detail : ", err);
        });
    }
}