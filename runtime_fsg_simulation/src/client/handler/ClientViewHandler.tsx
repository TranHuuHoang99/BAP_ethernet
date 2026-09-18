import * as React from 'react'
import { createRoot } from 'react-dom/client';
import { ComponentIndex_t, HELLO_WORLD_GET_TYPE } from '../../common/request_api.js';
import { globalClientRequestHandler } from './ClientRequestHandler.js';

export function HealthCheck() {
    const [isRunning, setBinaryState] = React.useState<boolean>(false);
    React.useEffect(() => {
        const onDataComes = (isAlive: boolean) => {
            setBinaryState(isAlive);
        }
        globalClientRequestHandler.subcribe(ComponentIndex_t.HEALTH_CHECK_FSG_RUNNING, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(ComponentIndex_t.HEALTH_CHECK_FSG_RUNNING);
        }
    }, []);
    const toggleExecuteBin = () => {
        globalClientRequestHandler.handleRequest(ComponentIndex_t.HEALTH_CHECK_FSG_RUNNING, !isRunning);
    };
    const buttonText = isRunning ? "OFF" : "ON";
    const buttonColor = isRunning ? "#F44336" : "#ffffff";
    return (
        <div style={{
            fontFamily: 'Arial, sans-serif',
            display: 'flex',
            flexDirection: 'column',
            alignItems: 'center',
            justifyContent: 'center',
            width: '100%',
            textAlign: 'center'
        }}>
            <h4>HEALTH CHECK</h4>
            <div>
                <div>
                    <label style={{ color: isRunning ? "#4CAF50" : "#F44336",
                                    fontWeight: 'bold' }}
                    >
                        {isRunning ? "System is Running" : "System is Stopped"}
                    </label>
                </div>
                <button
                    onClick={toggleExecuteBin}
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

export function FanSpeedZL() {
    const [speed, setSpeed] = React.useState<number>(0);
    const [modState, setModState] = React.useState<boolean>(false);
    const [modReason, setModReason] = React.useState<number>(0);

    React.useEffect(() => {
        const onDataComes = (_speed: number,
                             _modState: boolean,
                             _modReason: number) =>
        {
            setSpeed(_speed);
            setModState(_modState);
            setModReason(_modReason);
        }
        globalClientRequestHandler.subcribe(ComponentIndex_t.MODIFY_HVAC_FAN_SPEED_ZL, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(ComponentIndex_t.MODIFY_HVAC_FAN_SPEED_ZL);
        }
    }, []);

    const modReasonOption = Array.from({length:13}, (_, i) => i);
    const speedOption = Array.from({length:10}, (_, i) => i);
    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        globalClientRequestHandler.handleRequest(
            ComponentIndex_t.MODIFY_HVAC_FAN_SPEED_ZL,
            speed,
            modState,
            modReason
        )
    };
    return (
        <form onSubmit={handleSubmit}>
            <div>
                <h4>FAN SPEED ZONE LEFT</h4>
                <div style={{display: 'flex', gap: '20px'}}>
                    <div>
                        <div><label>SPEED</label></div>
                        <select
                            id='speed-left-select'
                            name='speed-left'
                            value={speed.toString()}
                            onChange={(e) => setSpeed(Number(e.target.value))}
                        >
                            {speedOption.map((speed_val) => (
                                <option key={speed_val} value={speed_val}>{speed_val}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>MODIFICATION STATE</label></div>
                        <select
                            id='speed-left-mod-state-select'
                            name='speed-left-mod-state'
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
                            id='speed-left-mod-reason-select'
                            name='speed-left-mod-reason'
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

export function FanSpeedZR() {
    const [speed, setSpeed] = React.useState<number>(0);
    const [modState, setModState] = React.useState<boolean>(false);
    const [modReason, setModReason] = React.useState<number>(0);

    React.useEffect(() => {
        const onDataComes = (_speed: number,
                             _modState: boolean,
                             _modReason: number) =>
        {
            setSpeed(_speed);
            setModState(_modState);
            setModReason(_modReason);
        }
        globalClientRequestHandler.subcribe(ComponentIndex_t.MODIFY_HVAC_FAN_SPEED_ZR, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(ComponentIndex_t.MODIFY_HVAC_FAN_SPEED_ZR);
        }
    }, []);

    const modReasonOption = Array.from({length:13}, (_, i) => i);
    const speedOption = Array.from({length:10}, (_, i) => i);
    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        globalClientRequestHandler.handleRequest(
            ComponentIndex_t.MODIFY_HVAC_FAN_SPEED_ZR,
            speed,
            modState,
            modReason
        )
    };
    return (
        <form onSubmit={handleSubmit}>
            <div>
                <h4>FAN SPEED ZONE RIGHT</h4>
                <div style={{display: 'flex', gap: '20px'}}>
                    <div>
                        <div><label>SPEED</label></div>
                        <select
                            id='speed-right-select'
                            name='speed-right'
                            value={speed.toString()}
                            onChange={(e) => setSpeed(Number(e.target.value))}
                        >
                            {speedOption.map((speed_val) => (
                                <option key={speed_val} value={speed_val}>{speed_val}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>MODIFICATION STATE</label></div>
                        <select
                            id='speed-right-mod-state-select'
                            name='speed-right-mod-state'
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
                            id='speed-right-mod-reason-select'
                            name='speed-right-mod-reason'
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

export function TirePressure() {
    const [unit, setUnit] = React.useState<number>(0);
    const [value_fl, setValueFL] = React.useState<number>(0.0);
    const [value_fr, setValueFR] = React.useState<number>(0.0);
    const [value_rl, setValueRL] = React.useState<number>(0.0);
    const [value_rr, setValueRR] = React.useState<number>(0.0);
    React.useEffect(() => {
        const onDataComes = (_unit: number,
                             _fl: number,
                             _fr: number,
                             _rl: number,
                             _rr: number) =>
        {
            setUnit(_unit);
            setValueFL(_fl);
            setValueFR(_fr);
            setValueRL(_rl);
            setValueRR(_rr);
        }
        globalClientRequestHandler.subcribe(ComponentIndex_t.MODIFY_TIRE_PRESSURE, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(ComponentIndex_t.MODIFY_TIRE_PRESSURE);
        }
    }, []);

    let unitOption = Array.from({length:3}, (_, i) => i);
    const valBAR = Array.from({length:64}, (_, i) => Number(i * 0.1).toFixed(1));
    const valPSI = Array.from({length:64}, (_, i) => i * 1.0);
    const valKPA = Array.from({length:64}, (_, i) => i * 10.0);
    const curValOption = unit === 0 ? valBAR : unit === 1 ? valPSI : valKPA;
    const unitNames = ["BAR", "PSI", "KPA"];
    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        globalClientRequestHandler.handleRequest(
            ComponentIndex_t.MODIFY_TIRE_PRESSURE,
            unit,
            value_fl,
            value_fr,
            value_rl,
            value_rr
        )
    };
    return (
        <form onSubmit={handleSubmit}>
            <div>
                <h4>TIRE PRESSURE</h4>
                <div style={{display: 'flex', gap: '20px'}}>
                    <div>
                        <div><label>UNIT</label></div>
                        <select
                            id='tire-pressure-unit-select'
                            name='tire-pressure-unit'
                            value={unit.toString()}
                            onChange={(e) => {setUnit(Number(e.target.value));}}
                        >
                            {unitOption.map((unit_val) => (
                                <option key={unit_val} value={unit_val}>
                                    {unitNames[unit_val]} | {unit_val}
                                </option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>VALUE FRONT LEFT</label></div>
                        <select
                            id='tire-pressure-fl-select'
                            name='tire-pressure-fl'
                            value={value_fl.toString()}
                            onChange={(e) => {setValueFL(Number(e.target.value));}}
                        >
                            {curValOption.map((val_fl) => (
                                <option key={val_fl} value={val_fl}>{val_fl}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>VALUE FRONT RIGHT</label></div>
                        <select
                            id='tire-pressure-fr-select'
                            name='tire-pressure-fr'
                            value={value_fr.toString()}
                            onChange={(e) => {setValueFR(Number(e.target.value));}}
                        >
                            {curValOption.map((val_fr) => (
                                <option key={val_fr} value={val_fr}>{val_fr}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>VALUE REAR LEFT</label></div>
                        <select
                            id='tire-pressure-rl-select'
                            name='tire-pressure-rl'
                            value={value_rl.toString()}
                            onChange={(e) => {setValueRL(Number(e.target.value));}}
                        >
                            {curValOption.map((val_rl) => (
                                <option key={val_rl} value={val_rl}>{val_rl}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>VALUE REAR RIGHT</label></div>
                        <select
                            id='tire-pressure-rr-select'
                            name='tire-pressure-rr'
                            value={value_rr.toString()}
                            onChange={(e) => {setValueRR(Number(e.target.value));}}
                        >
                            {curValOption.map((val_rr) => (
                                <option key={val_rr} value={val_rr}>{val_rr}</option>
                            ))}
                        </select>
                    </div>
                </div>
            </div>
            <button style={{marginTop: '6px'}} type='submit'>SEND</button>
        </form>
    )
}

export function SeatClimateZL() {
    const [heat_val, setHeatVal] = React.useState<number>(0);
    const [heat_state, setHeatState] = React.useState<number>(0);
    const [ven_val, setVenVal] = React.useState<number>(0);
    const [ven_state, setVenState] = React.useState<number>(0);

    React.useEffect(() => {
        const onDataComes = (_heat_val: number,
                             _heat_state: number,
                             _ven_val: number,
                             _ven_state: number) =>
        {
            setHeatVal(_heat_val);
            setHeatState(_heat_state);
            setVenVal(_ven_val);
            setVenState(_ven_state);
        }
        globalClientRequestHandler.subcribe(ComponentIndex_t.MODIFY_SEAT_CLIMATE_ZL, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(ComponentIndex_t.MODIFY_SEAT_CLIMATE_ZL);
        }
    }, []);

    const heatValOption = Array.from({length:4}, (_, i) => i);
    const heatStateOption = Array.from({length:3}, (_, i) => i);
    const venValOption = Array.from({length:4}, (_, i) => i);
    const venStateOption = Array.from({length:3}, (_, i) => i);
    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        globalClientRequestHandler.handleRequest(
            ComponentIndex_t.MODIFY_SEAT_CLIMATE_ZL,
            heat_val,
            heat_state,
            ven_val,
            ven_state
        )
    };
    return (
        <form onSubmit={handleSubmit}>
            <div>
                <h4>SEAT CLIMATE ZONE LEFT</h4>
                <div style={{display: 'flex', gap: '20px'}}>
                    <div>
                        <div><label>HEAT VAL</label></div>
                        <select
                            id='heat-val-left-select'
                            name='heat-val-left'
                            value={heat_val.toString()}
                            onChange={(e) => setHeatVal(Number(e.target.value))}
                        >
                            {heatValOption.map((heat_val) => (
                                <option key={heat_val} value={heat_val}>{heat_val}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>HEAT STATE</label></div>
                        <select
                            id='heat-state-left-select'
                            name='heat-state-left'
                            value={heat_state.toString()}
                            onChange={(e) => setHeatState(Number(e.target.value))}
                        >
                            {heatStateOption.map((heat_state) => (
                                <option key={heat_state} value={heat_state}>{heat_state}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>VENTILATION VAL</label></div>
                        <select
                            id='ven-val-left-select'
                            name='ven-val-left'
                            value={ven_val.toString()}
                            onChange={(e) => setVenVal(Number(e.target.value))}
                        >
                            {venValOption.map((ven_val_t) => (
                                <option key={ven_val_t} value={ven_val_t}>{ven_val_t}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>VENTILATION STATE</label></div>
                        <select
                            id='ven-state-left-select'
                            name='ven-state-left'
                            value={ven_state.toString()}
                            onChange={(e) => setVenState(Number(e.target.value))}
                        >
                            {venStateOption.map((ven_state_t) => (
                                <option key={ven_state_t} value={ven_state_t}>{ven_state_t}</option>
                            ))}
                        </select>
                    </div>
                </div>
            </div>
            <button style={{marginTop: '6px'}} type='submit'>SEND</button>
        </form>
    )
}

export function SeatClimateZR() {
    const [heat_val, setHeatVal] = React.useState<number>(0);
    const [heat_state, setHeatState] = React.useState<number>(0);
    const [ven_val, setVenVal] = React.useState<number>(0);
    const [ven_state, setVenState] = React.useState<number>(0);

    React.useEffect(() => {
        const onDataComes = (_heat_val: number,
                             _heat_state: number,
                             _ven_val: number,
                             _ven_state: number) =>
        {
            setHeatVal(_heat_val);
            setHeatState(_heat_state);
            setVenVal(_ven_val);
            setVenState(_ven_state);
        }
        globalClientRequestHandler.subcribe(ComponentIndex_t.MODIFY_SEAT_CLIMATE_ZR, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(ComponentIndex_t.MODIFY_SEAT_CLIMATE_ZR);
        }
    }, []);

    const heatValOption = Array.from({length:4}, (_, i) => i);
    const heatStateOption = Array.from({length:3}, (_, i) => i);
    const venValOption = Array.from({length:4}, (_, i) => i);
    const venStateOption = Array.from({length:3}, (_, i) => i);
    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        globalClientRequestHandler.handleRequest(
            ComponentIndex_t.MODIFY_SEAT_CLIMATE_ZR,
            heat_val,
            heat_state,
            ven_val,
            ven_state
        )
    };
    return (
        <form onSubmit={handleSubmit}>
            <div>
                <h4>SEAT CLIMATE ZONE RIGHT</h4>
                <div style={{display: 'flex', gap: '20px'}}>
                    <div>
                        <div><label>HEAT VAL</label></div>
                        <select
                            id='heat-val-right-select'
                            name='heat-val-right'
                            value={heat_val.toString()}
                            onChange={(e) => setHeatVal(Number(e.target.value))}
                        >
                            {heatValOption.map((heat_val) => (
                                <option key={heat_val} value={heat_val}>{heat_val}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>HEAT STATE</label></div>
                        <select
                            id='heat-state-right-select'
                            name='heat-state-right'
                            value={heat_state.toString()}
                            onChange={(e) => setHeatState(Number(e.target.value))}
                        >
                            {heatStateOption.map((heat_state) => (
                                <option key={heat_state} value={heat_state}>{heat_state}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>VENTILATION VAL</label></div>
                        <select
                            id='ven-val-right-select'
                            name='ven-val-right'
                            value={ven_val.toString()}
                            onChange={(e) => setVenVal(Number(e.target.value))}
                        >
                            {venValOption.map((ven_val_t) => (
                                <option key={ven_val_t} value={ven_val_t}>{ven_val_t}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>VENTILATION STATE</label></div>
                        <select
                            id='ven-state-right-select'
                            name='ven-state-right'
                            value={ven_state.toString()}
                            onChange={(e) => setVenState(Number(e.target.value))}
                        >
                            {venStateOption.map((ven_state_t) => (
                                <option key={ven_state_t} value={ven_state_t}>{ven_state_t}</option>
                            ))}
                        </select>
                    </div>
                </div>
            </div>
            <button style={{marginTop: '6px'}} type='submit'>SEND</button>
        </form>
    )
}

<<<<<<< Updated upstream
export function AirCirculationManual() {
    const [air_pos, setAirPos] = React.useState<number>(0);

    React.useEffect(() => {
        const onDataComes = (_air_pos: 0) => {
            setAirPos(_air_pos);
        }
        globalClientRequestHandler.subcribe(ComponentIndex_t.MODIFY_AIR_CIRC_MANUAL, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(ComponentIndex_t.MODIFY_AIR_CIRC_MANUAL);
        }
    }, []);

    const airPosOption = Array.from({length:2}, (_, i) => i);
    const airPosName = ["CABIN", "OUTSIDE"];
    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        globalClientRequestHandler.handleRequest(
            ComponentIndex_t.MODIFY_AIR_CIRC_MANUAL,
            air_pos
=======
export function TirePressure() {
    const [heat_val, setHeatVal] = React.useState<number>(0);
    const [heat_state, setHeatState] = React.useState<number>(0);
    const [ven_val, setVenVal] = React.useState<number>(0);
    const [ven_state, setVenState] = React.useState<number>(0);

    React.useEffect(() => {
        const onDataComes = (_heat_val: number,
                             _heat_state: number,
                             _ven_val: number,
                             _ven_state: number) =>
        {
            setHeatVal(_heat_val);
            setHeatState(_heat_state);
            setVenVal(_ven_val);
            setVenState(_ven_state);
        }
        globalClientRequestHandler.subcribe(ComponentIndex_t.MODIFY_SEAT_CLIMATE_ZR, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(ComponentIndex_t.MODIFY_SEAT_CLIMATE_ZR);
        }
    }, []);

    const heatValOption = Array.from({length:4}, (_, i) => i);
    const heatStateOption = Array.from({length:3}, (_, i) => i);
    const venValOption = Array.from({length:4}, (_, i) => i);
    const venStateOption = Array.from({length:3}, (_, i) => i);
    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        globalClientRequestHandler.handleRequest(
            ComponentIndex_t.MODIFY_SEAT_CLIMATE_ZR,
            heat_val,
            heat_state,
            ven_val,
            ven_state
>>>>>>> Stashed changes
        )
    };
    return (
        <form onSubmit={handleSubmit}>
            <div>
<<<<<<< Updated upstream
                <h4>AIR CIRCULATION MANUAL</h4>
                <div style={{display: 'flex', gap: '20px'}}>
                    <div>
                        <div><label>AIR CIRC OPT</label></div>
                        <select
                            id='air-circ-select'
                            name='air-circ'
                            value={air_pos.toString()}
                            onChange={(e) => setAirPos(Number(e.target.value))}
                        >
                            {airPosOption.map((air_pos_val) => (
                                <option key={air_pos_val} value={air_pos_val}>
                                    {airPosName[air_pos_val]} | {air_pos_val}
                                </option>
                            ))}
                        </select>
                    </div>
                </div>
            </div>
            <button style={{marginTop: '6px'}} type='submit'>SEND</button>
        </form>
    )
}

export function AirDistributionZL() {
    const [air_distr, setAirPos] = React.useState<number>(1);

    React.useEffect(() => {
        const onDataComes = (_air_distr: 0) => {
            setAirPos(_air_distr);
        }
        globalClientRequestHandler.subcribe(ComponentIndex_t.MODIFY_AIR_DIST_ZL, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(ComponentIndex_t.MODIFY_AIR_DIST_ZL);
        }
    }, []);

    const airDistrOpt = Array.from({length:3}, (_, i) => i + 1);
    const airDistrName = ["UP", "BODY", "FOOTWELL"];
    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        globalClientRequestHandler.handleRequest(
            ComponentIndex_t.MODIFY_AIR_DIST_ZL,
            air_distr
        )
    };
    return (
        <form onSubmit={handleSubmit}>
            <div>
                <h4>AIR DISTRIBUTION ZONE LEFT</h4>
                <div style={{display: 'flex', gap: '20px'}}>
                    <div>
                        <div><label>AIR CIRC OPT</label></div>
                        <select
                            id='air-distribution-zl-select'
                            name='air-distribution-zl'
                            value={air_distr.toString()}
                            onChange={(e) => setAirPos(Number(e.target.value))}
                        >
                            {airDistrOpt.map((air_distr_val) => (
                                <option key={air_distr_val} value={air_distr_val}>
                                    {airDistrName[air_distr_val-1]} | {air_distr_val}
                                </option>
                            ))}
                        </select>
                    </div>
                </div>
            </div>
            <button style={{marginTop: '6px'}} type='submit'>SEND</button>
        </form>
    )
}

export function AirDistributionZR() {
    const [air_distr, setAirPos] = React.useState<number>(1);

    React.useEffect(() => {
        const onDataComes = (_air_distr: 0) => {
            setAirPos(_air_distr);
        }
        globalClientRequestHandler.subcribe(ComponentIndex_t.MODIFY_AIR_DIST_ZR, onDataComes);
        return () => {
            globalClientRequestHandler.unsubcribe(ComponentIndex_t.MODIFY_AIR_DIST_ZR);
        }
    }, []);

    const airDistrOpt = Array.from({length:3}, (_, i) => i + 1);
    const airDistrName = ["UP", "BODY", "FOOTWELL"];
    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        globalClientRequestHandler.handleRequest(
            ComponentIndex_t.MODIFY_AIR_DIST_ZR,
            air_distr
        )
    };
    return (
        <form onSubmit={handleSubmit}>
            <div>
                <h4>AIR DISTRIBUTION ZONE RIGHT</h4>
                <div style={{display: 'flex', gap: '20px'}}>
                    <div>
                        <div><label>AIR CIRC OPT</label></div>
                        <select
                            id='air-distribution-zr-select'
                            name='air-distribution-zr'
                            value={air_distr.toString()}
                            onChange={(e) => setAirPos(Number(e.target.value))}
                        >
                            {airDistrOpt.map((air_distr_val) => (
                                <option key={air_distr_val} value={air_distr_val}>
                                    {airDistrName[air_distr_val-1]} | {air_distr_val}
                                </option>
=======
                <h4>SEAT CLIMATE ZONE RIGHT</h4>
                <div style={{display: 'flex', gap: '20px'}}>
                    <div>
                        <div><label>HEAT VAL</label></div>
                        <select
                            id='heat-val-right-select'
                            name='heat-val-right'
                            value={heat_val.toString()}
                            onChange={(e) => setHeatVal(Number(e.target.value))}
                        >
                            {heatValOption.map((heat_val) => (
                                <option key={heat_val} value={heat_val}>{heat_val}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>HEAT STATE</label></div>
                        <select
                            id='heat-state-right-select'
                            name='heat-state-right'
                            value={heat_state.toString()}
                            onChange={(e) => setHeatState(Number(e.target.value))}
                        >
                            {heatStateOption.map((heat_state) => (
                                <option key={heat_state} value={heat_state}>{heat_state}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>VENTILATION VAL</label></div>
                        <select
                            id='ven-val-right-select'
                            name='ven-val-right'
                            value={ven_val.toString()}
                            onChange={(e) => setVenVal(Number(e.target.value))}
                        >
                            {venValOption.map((ven_val_t) => (
                                <option key={ven_val_t} value={ven_val_t}>{ven_val_t}</option>
                            ))}
                        </select>
                    </div>
                    <div>
                        <div><label>VENTILATION STATE</label></div>
                        <select
                            id='ven-state-right-select'
                            name='ven-state-right'
                            value={ven_state.toString()}
                            onChange={(e) => setHeatState(Number(e.target.value))}
                        >
                            {venStateOption.map((ven_state_t) => (
                                <option key={ven_state_t} value={ven_state_t}>{ven_state_t}</option>
>>>>>>> Stashed changes
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

export function AppView() {
    return (
        <div style={{ display: 'flex', flexDirection: 'column', gap: '20px', padding: '20px' }}>
            
            <div style={{ ...cardRowStyle, justifyContent: 'center'}}>
                <HealthCheck />
            </div>

            <div style={cardRowStyle}>
                <HvacPowerStatus />
                <div style={dividerStyle} />
                <AcCompressorForm />
                <div style={dividerStyle} />
                <AcCompressorEcoMaxForm />
            </div>

            <div style={cardRowStyle}>
                <TemperatureZL />
                <div style={dividerStyle} />
                <TemperatureZR />
            </div>

            <div style={cardRowStyle}>
                <FanSpeedZL />
                <div style={dividerStyle} />
                <FanSpeedZR />
                <div style={dividerStyle} />
                <TirePressure />
            </div>

            <div style={cardRowStyle}>
                <SeatClimateZL />
                <div style={dividerStyle} />
                <SeatClimateZR />
                <div style={dividerStyle} />
                <AirCirculationManual />
            </div>

            <div style={cardRowStyle}>
                <AirDistributionZL />
                <div style={dividerStyle} />
                <AirDistributionZR />
            </div>

        </div>
    );
}

const cardRowStyle: React.CSSProperties = {
    display: 'flex',
    flexDirection: 'row',
    gap: '30px',
    padding: '20px',
    border: '1px solid #ccc',
    borderRadius: '8px',
    boxShadow: '0 2px 4px rgba(0,0,0,0.05)',
    alignItems: 'flex-start'
};

const dividerStyle: React.CSSProperties = {
    width: '1px',
    backgroundColor: '#ccc',
    alignSelf: 'stretch',
    margin: '0 10px'
};
