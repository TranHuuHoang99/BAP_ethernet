import * as fs from 'fs'

const PIPE_NAME = '\\\\.\\pipe\\MyNamedPipe';
export class SimulationHandler {
    constructor()
    {

    }

    public executeRequest(payload: Uint8Array): void
    {
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