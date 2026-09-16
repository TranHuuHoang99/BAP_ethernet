#ifndef __FSG_DEFAULT_VALUE_HPP__
#define __FSG_DEFAULT_VALUE_HPP__

#include "FsgType.hpp"

namespace http {

typedef enum class HTTP_REQUEST_TYPE : uint8_t {
    INVALID = 0u,
    MODIFY_HVAC_STATUS,
    MODIFY_AC_COMPRESSOR_STATUS,
    MODIFY_AC_COMPRESSOR_ECO_MAX,
    MODIFY_HVAC_TEMP_ZL,
    MODIFY_HVAC_TEMP_ZR,
    MODIFY_HVAC_FAN_SPEED_ZL,
    MODIFY_HVAC_FAN_SPEED_ZR,
    MODIFY_RVC,
    MODIFY_SEAT_CLIMATE_ZL,
    MODIFY_SEAT_CLIMATE_ZR,
    MODIFY_AIR_CIRC_MANUAL,
    MODIFY_AIR_DIST_ZL,
    MODIFY_AIR_DIST_ZR,
} HttpRequestType_t;

/*
    HVAC POWER SIGNAL
*/
inline bool hvac_power_cmd = false;
inline bool hvac_power_status = false;

/*
    AC COMPRESSOR SIGNAL
*/
inline bool ac_compressor_cmd = false;
inline bool ac_compressor_status = false;
inline bool ac_compressor_eco_max = false;
// 0 mean eco, 1 mean max
inline int32_t ac_compressor_mode = 0;
// HVAC notify modification state. 0 can be modified, 1 cannot be modifed
inline int32_t ac_modification_state = 0;
// 0x3=engine_not_running
inline int32_t ac_modifcation_reason = 0;


/*
    ZL TEMPERATURE
*/
// 0 is C, 1 is F
inline int32_t zl_temp_unit = 0;
inline float32_t zl_temp_value = 22.0f;
inline int32_t zl_temp_modification_state = 0;
inline int32_t zl_temp_modification_reason = 0;

/*
    ZR TEMPERATURE
*/
// 0 is C, 1 is F
inline int32_t zr_temp_unit = 0;
inline float32_t zr_temp_value = 22.0f;
inline int32_t zr_temp_modification_state = 0;
inline int32_t zr_temp_modification_reason = 0;

/*
    ZL AIR VOLUME
*/
inline int32_t zl_air_volume = 1;
inline int32_t zl_air_volume_modification_state = 0;
inline int32_t zl_air_volume_modification_reason = 0;

/*
    ZR AIR VOLUME
*/
inline int32_t zr_air_volume = 1;
inline int32_t zr_air_volume_modification_state = 0;
inline int32_t zr_air_volume_modification_reason = 0;

/*
    RVC view
*/
inline bool isRequestedRvc = false;
inline bool rvcStatus = false;

/*
    TIRE PRESSURES
*/
inline int32_t tire_pressure_unit = 0;
inline float32_t fl_tire_pressure_val = 0.0f;
inline float32_t fr_tire_pressure_val = 0.0f;
inline float32_t rl_tire_pressure_val = 0.0f;
inline float32_t rt_tire_pressure_val = 0.0f;

/*
    ZL SEAT CLIMATE
*/
inline int32_t zl_seat_climate_heat_state = 0;
inline int32_t zl_seat_climate_heat_value = 0;
inline int32_t zl_seat_climate_heat_cmd = 0;
inline int32_t zl_seat_climate_ventilation_state = 0;
inline int32_t zl_seat_climate_ventilation_value = 0;
inline int32_t zl_seat_climate_ventilation_cmd = 0;

/*
    ZR SEAT CLIMATE
*/
inline int32_t zr_seat_climate_heat_state = 0;
inline int32_t zr_seat_climate_heat_value = 0;
inline int32_t zr_seat_climate_heat_cmd = 0;
inline int32_t zr_seat_climate_ventilation_state = 0;
inline int32_t zr_seat_climate_ventilation_value = 0;
inline int32_t zr_seat_climate_ventilation_cmd = 0;

/*
    AIR CIRCULATION MANUAL CONTROL
*/
inline bool air_circulation_manual_state = false;
inline bool air_circulation_manual_cmd = false;

/*
    ZL AIR DISTRIBUTION
*/
inline int32_t zl_air_distribution_control = 0;
inline int32_t zl_air_distribution_state = 0;

/*
    ZR AIR DISTRIBUTION
*/
inline int32_t zr_air_distribution_control = 0;
inline int32_t zr_air_distribution_state = 0;

};

#endif // __FSG_DEFAULT_VALUE_HPP__
