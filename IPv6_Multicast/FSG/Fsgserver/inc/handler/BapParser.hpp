#ifndef __BAP_PARSER_HPP__
#define __BAP_PARSER_HPP__

#include "FsgType.hpp"

using std::_Placeholder;

class BapParser {
private:
    struct BapParserToken {
        explicit BapParserToken(void) = default;
    };

    std::map<std::pair<lsgId_t, fctId_t>, std::any> m_distributedFunc_map = {
        {
            {lsgId_t::BapLsg_ClimateZone, fctId_t::BapFct_ClimateZone_FSG_Control}, 
            std::function<void(uint8_t)>([&](uint8_t status) {
                this->decode_hvac_power(status);
            })
        },
    };
public:
    BapParser(BapParser::BapParserToken) {}
    BapParser(const BapParser&) = delete;
    BapParser& operator=(const BapParser&) = delete;
    ~BapParser(void);
    static std::shared_ptr<BapParser> instance(void);

    void load_initial_vals(void);
    
    /*
        encode : http request -> FSG simulation -> ASG linux
        decode : FSG simulation -> update http view
    */
    void encode_hvac_power(const bool cmd);
    void decode_hvac_power(const uint8_t status);

    void encode_ac_compressor_status(const bool status,
                                     const bool modi_state,
                                     const int32_t modi_reason);
    // void decode_ac_compressor_status

    void encode_ac_compressor_eco_max(const bool status,
                                      const bool modi_state,
                                      const int32_t modi_reason);
    // void decode_ac_compressor_eco_max

    void encode_temp_zl(const float32_t value,
                        const int32_t unit,
                        const bool modi_state,
                        const int32_t modi_reason);
    // void decode_temp_zl

    void encode_temp_zr(const float32_t value,
                        const int32_t unit,
                        const bool modi_state,
                        const int32_t modi_reason);
    // void decode_temp_zr

    void encode_fan_speed_zl(const int32_t value,
                             const bool modi_state,
                             const int32_t modi_reason);
    // void decode_fan_speed_zl

    void encode_fan_speed_zr(const int32_t value,
                             const bool modi_state,
                             const int32_t modi_reason);
    // void decode_fan_speed_zr

    void encode_rvc(const bool status);
    // void decode_rvc

    void encode_seat_climate_zl(const int32_t heat_val,
                                const int32_t heat_state,
                                const int32_t ventilation_val,
                                const int32_t ventilation_state);
    // void decode_seat_climate_zl

    void encode_seat_climate_zr(const int32_t heat_val,
                                const int32_t heat_state,
                                const int32_t ventilation_val,
                                const int32_t ventilation_state);
    // void decode_seat_climate_zr

    void encode_air_circulation_manual(const bool value);
    // void decode_air_circulation_manual

    void encode_air_distribution_zl(const int32_t value);
    // void decode_air_distribution_zl

    void encode_air_distribution_zr(const int32_t value);
    // void decode_air_distribution_zr
};

#endif // __BAP_PARSER_HPP__
