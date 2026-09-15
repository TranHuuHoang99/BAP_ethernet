
import { createServer } from 'node:http';
import { readFile } from 'node:fs/promises';
import { join } from 'node:path';
import { FSG_HTTP_PORT } from '../../common/common.js';

export class HttpRequestHandler {
    private readonly m_server = createServer(async (request, response) => {
        try {
            const requestPath = new URL(request.url ?? '/', 'http://localhost').pathname;
            const relativePath = requestPath === '/' ? 'index.html' : requestPath.slice(1);
            const filePath = join(process.cwd(), relativePath);
            const file = await readFile(filePath);
            const contentType = filePath.endsWith('.js')
                ? 'text/javascript; charset=utf-8'
                : 'text/html; charset=utf-8';
            response.writeHead(200, { 'Content-Type': contentType });
            response.end(file);
        } catch (error) {
            console.error('Unable to serve index.html:', error);
            response.writeHead(404, { 'Content-Type': 'text/plain; charset=utf-8' });
            response.end('File not found');
        }
    });

    public start(): void {
        this.m_server.listen(FSG_HTTP_PORT, () => {
            console.log(`HTTP server listening on http://0.0.0.0:${FSG_HTTP_PORT}`);
        });
    }
}
