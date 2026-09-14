import * as React from 'react'
import { globalSocketHandler } from './ClientSocketHandler.js';
import { ID_HELLO_WORLD } from '../common.js';
import { createRoot } from 'react-dom/client';

export function AppView() {
    return (
        <div>
            <RequestHelloWorldData />
        </div>
    );
}

export function RequestHelloWorldData() {
    const [message, setMessage] = React.useState<string>('Data empty');
    React.useEffect(() => {
        const onDataComes = (serverData: string) => {
            console.log("received data");
            setMessage(serverData);
        }
        globalSocketHandler.subcribe(ID_HELLO_WORLD, onDataComes);
        return () => {
            globalSocketHandler.unsubcribe(ID_HELLO_WORLD);
        };
    }, []);

    const handlerTriggerButton = () => {
        globalSocketHandler.sendRequest('GET_DATA');
    };

    return (
        <div>
            <h1>{message}</h1>
            <button onClick={handlerTriggerButton}> get data </button>
        </div>
    );
}

const container = document.getElementById('root');
if (container) {
    const root = createRoot(container);
    root.render(
        <React.StrictMode>
            <AppView />
        </React.StrictMode>
    )
}
