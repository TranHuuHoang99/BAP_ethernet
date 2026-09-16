import * as React from 'react'
import { createRoot } from 'react-dom/client';
import { ComponentIndex_t, HELLO_WORLD_GET_TYPE } from '../../common/request_api.js';
import { globalClientRequestHandler } from './ClientRequestHandler.js';

export function AppView() {
    return (
        <div>
            <HvacPowerStatus />
            <AcCompressorForm />
            <AcCompressorEcoMaxForm />
            <TemperatureZL />
            <TemperatureZR />
        </div>
    );
}

export function HvacPowerStatus() {
    const [isHvacOn, setHvacState] = React.useState<boolean>(false);
    React.useEffect(() => {
        const onDataComes = (hvacStatus: boolean) => {
            console.log("do change hvac status on UI");
            setHvacState(hvacStatus);
        }
        globalClientRequestHandler.subcribe(ComponentIndex_t.MODIFY_HVAC_POWER_STATUS, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(ComponentIndex_t.MODIFY_HVAC_POWER_STATUS);
        };
    }, []);
    const toggleHvacPower = () => {
        globalClientRequestHandler.handleRequest(ComponentIndex_t.MODIFY_HVAC_POWER_STATUS, !isHvacOn);
    };

    const buttonText = isHvacOn ? "ON" : "OFF";
    const buttonColor = isHvacOn ? "#4CAF50" : "#ffffff";
    return (
        <div style={{ fontFamily: 'Arial, sans-serif' }}>
            <h4>HVAC POWER</h4>
            <div>
                <div><label>status</label></div>
                <button
                    onClick={toggleHvacPower}
                    style={{
                        backgroundColor: buttonColor,
                        marginTop: '6px'
                    }}
                >
                    {buttonText}
                </button>
            </div>
        </div>
    );
}

export function AcCompressorForm() {
    const [status, setStatus] = React.useState<boolean>(false);
    const [modState, setModState] = React.useState<boolean>(false);
    const [modReason, setModReason] = React.useState<number>(0);

    React.useEffect(() => {
        const onDataComes = (_status: boolean, _modState: boolean, _modReason: number) => {
            setStatus(_status);
            setModState(_modState);
            setModReason(_modReason);
        }
        globalClientRequestHandler.subcribe(ComponentIndex_t.MODIFY_AC_COMPRESSOR_STATUS, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(ComponentIndex_t.MODIFY_AC_COMPRESSOR_STATUS);
        }
    }, []);

    // generate array from 0 -> 12
    const modReasonOption = Array.from({length:13}, (_, i) => i);
    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        globalClientRequestHandler.handleRequest(
            ComponentIndex_t.MODIFY_AC_COMPRESSOR_STATUS,
            status,
            modState,
            modReason
        )
    };
    return (
        <form onSubmit={handleSubmit}>
            <div>
                <h4>AC COMPRESSOR STATUS</h4>
                <div style={{display: 'flex', gap: '20px'}}>
                    <div>
                        <div><label>STATUS</label></div>
                        <select
                            id='ac-compressor-status-select'
                            name='ac-compressor-status'
                            value={status.toString()}
                            onChange={(e) => setStatus(e.target.value === 'true')}
                        >
                            <option value={"false"}>OFF</option>
                            <option value={"true"}>ON</option>
                        </select>
                    </div>
                    <div>
                        <div><label>MODIFICATION STATE</label></div>
                        <select
                            id='ac-compressor-mod-state-select'
                            name='ac-compressor-mod-state'
                            value={modState.toString()}
                            onChange={(e) => setModState(e.target.value === 'true')}
                        >
                            <option value={"false"}>CAN NOT BE CHANGED</option>
                            <option value={"true"}>CAN BE CHANGED</option>
                        </select>
                    </div>
                    <div>
                        <div><label>MODIFICATION REASON</label></div>
                        <select
                            id='ac-compressor-mod-reason-select'
                            name='ac-compressor-mod-reason'
                            value={modReason.toString()}
                            onChange={(e) => setModReason(Number(e.target.value))}
                        >
                            {modReasonOption.map((numb) => (
                                <option key={numb} value={numb}>{numb}</option>
                            ))}
                        </select>
                    </div>
                </div>
            </div>
            <button style={{marginTop: '6px'}} type='submit'>SEND</button>
        </form>
    )
}

export function AcCompressorEcoMaxForm() {
    const [mode, setStatus] = React.useState<boolean>(false);
    const [modState, setModState] = React.useState<boolean>(false);
    const [modReason, setModReason] = React.useState<number>(0);

    React.useEffect(() => {
        const onDataComes = (_mode: boolean, _modState: boolean, _modReason: number) => {
            setStatus(_mode);
            setModState(_modState);
            setModReason(_modReason);
        }
        globalClientRequestHandler.subcribe(ComponentIndex_t.MODIFY_AC_COMPRESSOR_ECO_MAX, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(ComponentIndex_t.MODIFY_AC_COMPRESSOR_ECO_MAX);
        }
    }, []);

    // generate array from 0 -> 12
    const modReasonOption = Array.from({length:13}, (_, i) => i);
    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        globalClientRequestHandler.handleRequest(
            ComponentIndex_t.MODIFY_AC_COMPRESSOR_ECO_MAX,
            mode,
            modState,
            modReason
        )
    };
    return (
        <form onSubmit={handleSubmit}>
            <div>
                <h4>AC COMPRESSOR ECO MAX MODE</h4>
                <div style={{display: 'flex', gap: '20px'}}>
                    <div>
                        <div><label>MODE</label></div>
                        <select
                            id='ac-compressor-eco-max-select'
                            name='ac-compressor-eco-max'
                            value={mode.toString()}
                            onChange={(e) => setStatus(e.target.value === 'true')}
                        >
                            <option value={"false"}>ECO</option>
                            <option value={"true"}>MAX</option>
                        </select>
                    </div>
                    <div>
                        <div><label>MODIFICATION STATE</label></div>
                        <select
                            id='ac-compressor-eco-max-mod-state-select'
                            name='ac-compressor-eco-max-mod-state'
                            value={modState.toString()}
                            onChange={(e) => setModState(e.target.value === 'true')}
                        >
                            <option value={"false"}>CAN NOT BE CHANGED</option>
                            <option value={"true"}>CAN BE CHANGED</option>
                        </select>
                    </div>
                    <div>
                        <div><label>MODIFICATION REASON</label></div>
                        <select
                            id='ac-compressor-eco-max-mod-reason-select'
                            name='ac-compressor-eco-max-mod-reason'
                            value={modReason.toString()}
                            onChange={(e) => setModReason(Number(e.target.value))}
                        >
                            {modReasonOption.map((numb) => (
                                <option key={numb} value={numb}>{numb}</option>
                            ))}
                        </select>
                    </div>
                </div>
            </div>
            <button style={{marginTop: '6px'}} type='submit'>SEND</button>
        </form>
    )
}

export function TemperatureZL() {
    const [temperature, setTemperature] = React.useState<number>(22.0);
    const [unit, setUnit] = React.useState<number>(0);
    const [modState, setModState] = React.useState<boolean>(false);
    const [modReason, setModReason] = React.useState<number>(0);

    React.useEffect(() => {
        const onDataComes = (_temp: number,
                             _unit: number,
                             _modState: boolean,
                             _modReason: number) =>
        {
            setTemperature(_temp);
            setUnit(_unit);
            setModState(_modState);
            setModReason(_modReason);
        }
        globalClientRequestHandler.subcribe(ComponentIndex_t.MODIFY_HVAC_TEMP_ZL, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(ComponentIndex_t.MODIFY_HVAC_TEMP_ZL);
        }
    }, []);

    const modReasonOption = Array.from({length:13}, (_, i) => i);
    const tempOption = Array.from({length:52}, (_, i) => 10 + i*0.5);
    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        globalClientRequestHandler.handleRequest(
            ComponentIndex_t.MODIFY_HVAC_TEMP_ZL,
            temperature,
            unit,
            modState,
            modReason
        )
    };
    return (
        <form onSubmit={handleSubmit}>
            <div>
                <h4>TEMPERATURE ZONE LEFT</h4>
                <div style={{display: 'flex', gap: '20px'}}>
                    <div>
                        <div><label>TEMPERATURE</label></div>
                        <select
                            id='temp-left-select'
                            name='temp-left'
                            value={temperature.toString()}
                            onChange={(e) => setTemperature(Number(e.target.value))}
                        >
                            {tempOption.map((temp_val) => (
                                <option key={temp_val} value={temp_val}>{temp_val}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>UNIT</label></div>
                        <select
                            id='unit-left-select'
                            name='unit-left'
                            value={unit.toString()}
                            onChange={(e) => setUnit(Number(e.target.value))}
                        >
                            <option value={0}>CELSIUS</option>
                            <option value={1}>FAHRENHEIT</option>
                        </select>
                    </div>
                    <div>
                        <div><label>MODIFICATION STATE</label></div>
                        <select
                            id='temp-left-mod-state-select'
                            name='temp-left-mod-state'
                            value={modState.toString()}
                            onChange={(e) => setModState(e.target.value === 'true')}
                        >
                            <option value={"false"}>CAN NOT BE CHANGED</option>
                            <option value={"true"}>CAN BE CHANGED</option>
                        </select>
                    </div>
                    <div>
                        <div><label>MODIFICATION REASON</label></div>
                        <select
                            id='temp-left-mod-reason-select'
                            name='temp-left-mod-reason'
                            value={modReason.toString()}
                            onChange={(e) => setModReason(Number(e.target.value))}
                        >
                            {modReasonOption.map((numb) => (
                                <option key={numb} value={numb}>{numb}</option>
                            ))}
                        </select>
                    </div>
                </div>
            </div>
            <button style={{marginTop: '6px'}} type='submit'>SEND</button>
        </form>
    )
}

export function TemperatureZR() {
    const [temperature, setTemperature] = React.useState<number>(22.0);
    const [unit, setUnit] = React.useState<number>(0);
    const [modState, setModState] = React.useState<boolean>(false);
    const [modReason, setModReason] = React.useState<number>(0);

    React.useEffect(() => {
        const onDataComes = (_temp: number,
                             _unit: number,
                             _modState: boolean,
                             _modReason: number) =>
        {
            setTemperature(_temp);
            setUnit(_unit);
            setModState(_modState);
            setModReason(_modReason);
        }
        globalClientRequestHandler.subcribe(ComponentIndex_t.MODIFY_HVAC_TEMP_ZR, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(ComponentIndex_t.MODIFY_HVAC_TEMP_ZR);
        }
    }, []);

    const modReasonOption = Array.from({length:13}, (_, i) => i);
    const tempOption = Array.from({length:52}, (_, i) => 10 + i*0.5);
    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        globalClientRequestHandler.handleRequest(
            ComponentIndex_t.MODIFY_HVAC_TEMP_ZR,
            temperature,
            unit,
            modState,
            modReason
        )
    };
    return (
        <form onSubmit={handleSubmit}>
            <div>
                <h4>TEMPERATURE ZONE RIGHT</h4>
                <div style={{display: 'flex', gap: '20px'}}>
                    <div>
                        <div><label>TEMPERATURE</label></div>
                        <select
                            id='temp-left-select'
                            name='temp-left'
                            value={temperature.toString()}
                            onChange={(e) => setTemperature(Number(e.target.value))}
                        >
                            {tempOption.map((temp_val) => (
                                <option key={temp_val} value={temp_val}>{temp_val}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>UNIT</label></div>
                        <select
                            id='unit-left-select'
                            name='unit-left'
                            value={unit.toString()}
                            onChange={(e) => setUnit(Number(e.target.value))}
                        >
                            <option value={0}>CELSIUS</option>
                            <option value={1}>FAHRENHEIT</option>
                        </select>
                    </div>
                    <div>
                        <div><label>MODIFICATION STATE</label></div>
                        <select
                            id='temp-right-mod-state-select'
                            name='temp-right-mod-state'
                            value={modState.toString()}
                            onChange={(e) => setModState(e.target.value === 'true')}
                        >
                            <option value={"false"}>CAN NOT BE CHANGED</option>
                            <option value={"true"}>CAN BE CHANGED</option>
                        </select>
                    </div>
                    <div>
                        <div><label>MODIFICATION REASON</label></div>
                        <select
                            id='temp-right-mod-reason-select'
                            name='temp-right-mod-reason'
                            value={modReason.toString()}
                            onChange={(e) => setModReason(Number(e.target.value))}
                        >
                            {modReasonOption.map((numb) => (
                                <option key={numb} value={numb}>{numb}</option>
                            ))}
                        </select>
                    </div>
                </div>
            </div>
            <button style={{marginTop: '6px'}} type='submit'>SEND</button>
        </form>
    )
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
