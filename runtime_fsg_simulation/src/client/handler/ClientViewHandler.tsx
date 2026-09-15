import * as React from 'react'
import { createRoot } from 'react-dom/client';
import { HELLO_WORLD_GET_TYPE, REQUEST_HVAC_POWER } from '../../common/request_api.js';
import { globalClientRequestHandler } from './ClientRequestHandler.js';

export function AppView() {
    return (
        <div>
            <RequestHelloWorldData />
            <RequestSetHvacPower />
        </div>
    );
}

export function RequestHelloWorldData() {
    const [message, setMessage] = React.useState<string>('Data empty');
    React.useEffect(() => {
        const onDataComes = (serverData: string) => {
            console.log("do change data on, ", HELLO_WORLD_GET_TYPE);
            setMessage(serverData);
        }
        globalClientRequestHandler.subcribe(HELLO_WORLD_GET_TYPE, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(HELLO_WORLD_GET_TYPE);
        };
    }, []);

    const handlerTriggerButton = () => {
        globalClientRequestHandler.handleRequest(HELLO_WORLD_GET_TYPE);
    };

    return (
        <div>
            <h1>{message}</h1>
            <button onClick={handlerTriggerButton}> get data </button>
        </div>
    );
}

export function RequestSetHvacPower() {
    const [isHvacOn, setHvacState] = React.useState<boolean>(false);
    React.useEffect(() => {
        const onDataComes = (hvacStatus: boolean) => {
            console.log("do change hvac status on UI");
            setHvacState(hvacStatus);
        }
        globalClientRequestHandler.subcribe(REQUEST_HVAC_POWER, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(REQUEST_HVAC_POWER);
        };
    });
    const toggleHvacPower = () => {
        globalClientRequestHandler.handleRequest(REQUEST_HVAC_POWER, !isHvacOn);
    };

    const buttonText = isHvacOn ? "ON" : "OFF";
    const buttonColor = isHvacOn ? "#4CAF50" : "#888888";
    return (
        <div style={{ padding: '20px', fontFamily: 'Arial, sans-serif' }}>
            <h3>Switch HVAC power : {buttonText}</h3>
            
            <button onClick={toggleHvacPower}
                    style={{
                    backgroundColor: buttonColor,
                    color: 'white',
                    padding: '10px 30px',
                    fontSize: '16px',
                    fontWeight: 'bold',
                    border: 'none',
                    borderRadius: '5px',
                    cursor: 'pointer',
                    transition: 'background-color 0.3s ease'}}
            >
                {buttonText}
            </button>
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
