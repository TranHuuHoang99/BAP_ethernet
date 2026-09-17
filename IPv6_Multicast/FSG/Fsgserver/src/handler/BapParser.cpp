#include "BapParser.hpp"
#include "FsgIpv6.hpp"
#include "FsgDefaultValue.hpp"

std::shared_ptr<BapParser> BapParser::instance(void)
{
    static std::shared_ptr<BapParser> _instance =\
    std::make_unique<BapParser>(BapParser::BapParserToken{});
    return _instance;
}

BapParser::~BapParser(void)
{

}

void BapParser::load_initial_vals(void)
{
    encode_hvac_power(http::hvac_power_status);
    encode_ac_compressor_status(http::ac_compressor_status,
                                http::ac_modification_state,
                                http::ac_modifcation_reason);
    encode_ac_compressor_eco_max(http::ac_compressor_eco_max,
                                 http::ac_modification_state,
                                 http::ac_modifcation_reason);
    encode_temp_zl(http::zl_temp_value,
                   http::zl_temp_unit,
                   http::zl_temp_modification_state,
                   http::zl_temp_modification_reason);
    encode_temp_zl(http::zr_temp_value,
                   http::zr_temp_unit,
                   http::zr_temp_modification_state,
                   http::zr_temp_modification_reason);
    encode_fan_speed_zl(http::zl_air_volume,
                        http::zl_air_volume_modification_state,
                        http::zl_air_volume_modification_reason);
    encode_fan_speed_zl(http::zr_air_volume,
                        http::zr_air_volume_modification_state,
                        http::zr_air_volume_modification_reason);
    encode_seat_climate_zl(http::zl_seat_climate_heat_value,
                           http::zl_seat_climate_heat_state,
                           http::zl_seat_climate_ventilation_value,
                           http::zl_seat_climate_ventilation_state);
    encode_seat_climate_zr(http::zr_seat_climate_heat_value,
                           http::zr_seat_climate_heat_state,
                           http::zr_seat_climate_ventilation_value,
                           http::zr_seat_climate_ventilation_state);
    encode_air_circulation_manual(http::air_circulation_manual_state);
    encode_air_distribution_zl(http::zl_air_distribution_state);
    encode_air_distribution_zr(http::zr_air_distribution_state);
}

void BapParser::encode_hvac_power(const bool cmd)
{
    std::cout << "[ENCODE] hvac power cmd : " << cmd << '\n';
    http::hvac_power_status = cmd;
    const std::shared_ptr<FsgIpv6> fsg = FsgIpv6::instance();
    if (fsg == nullptr) {
        std::cerr << "fsg is nullptr\n";
        return;
    }
    /*
        base on page 29 of document : BAP-FC_ClimateZone_P30DF7.17_V5.17.0_F.pdf
        set bit 4 of uint8_t value to be one is turn on fsg other wise turn off
    */
    auto [data, len] = fsg->loadData<uint8_t>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_FSG_Control
    );
    if (cmd) {
        data |= (1 << 4); // turn on bit 4
    } else {
        data &= ~(1 << 4); // turn off bit 4
    }
    const int32_t ret_store = fsg->storeData<uint8_t>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_FSG_Control,
        {data, len}
    );
    fsg->write_hvac_power_status(data);
}

void BapParser::decode_hvac_power(const uint8_t status)
{
    std::cout << "[DECODE] hvac power cmd : " << (int32_t)status << '\n';
    const std::shared_ptr<FsgIpv6> fsg = FsgIpv6::instance();
    if (fsg == nullptr) {
        std::cerr << "fsg is nullptr\n";
        return;
    }

    /*
        base on page 29 of document : BAP-FC_ClimateZone_P30DF7.17_V5.17.0_F.pdf
        set bit 4 of uint8_t value to be one is turn on fsg other wise turn off
    */
    auto [data, len] = fsg->loadData<uint8_t>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_FSG_Control
    );
    data = status;
    const int32_t ret_store = fsg->storeData<uint8_t>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_FSG_Control,
        {data, len}
    );
    const bool gt_hvac_power_val = (bool)((1 << 4) & status);
    http::hvac_power_cmd = gt_hvac_power_val;
    // this will be sent to HTTP view
}

void BapParser::encode_ac_compressor_status(const bool status,
                                            const bool modi_state,
                                            const int32_t modi_reason)
{
    /*
        base on page 38 - 41 of document : BAP-FC_ClimateMaster_P31DF3.19_V1.19.0_F.pdf
        - the first byte is used for controlling AC
            - bit 0 is for AC ON/OFF
            - bit 1 is for AC MAX ON/OFF
            - bit 2 is for AC ECO MODE ON/OFF
            - bit 3 is for MAX AC REAR ON/OFF
            - bit 4-7 is reserved
    */
    http::ac_compressor_status = status;
    http::ac_modification_state = modi_state;
    http::ac_modifcation_reason = modi_reason;
    const std::shared_ptr<FsgIpv6> fsg = FsgIpv6::instance();
    if (fsg == nullptr) {
        std::cerr << "fsg is nullptr\n";
        return;
    }
    auto [data, len] = fsg->loadData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateMaster,
        fctId_t::BapFct_ClimateMaster_AC
    );
    if (status) {
        data[0] |= (1 << 0);
    } else {
        data[0] &= ~(1 << 0);
    }

    /* modifition state */
    if (modi_state) {
        // can change
        data[len-1] |= (1 << 0);
    } else {
        // can not change
        data[len-1] &= ~(1 << 0);
    }

    /* modifition reason */
    data[len-1] &= 0x0F;
    data[len-1] |= (uint8_t)(modi_reason << 4);

    (void)fsg->storeData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateMaster,
        fctId_t::BapFct_ClimateMaster_AC,
        {data, len}
    );
    fsg->write_ac_compressor_status(data);
}

void BapParser::encode_ac_compressor_eco_max(const bool status,
                                             const bool modi_state,
                                             const int32_t modi_reason)
{
    /*
        base on page 38 - 41 of document : BAP-FC_ClimateMaster_P31DF3.19_V1.19.0_F.pdf
        - the first byte is used for controlling AC
            - bit 0 is for AC ON/OFF
            - bit 1 is for AC MAX ON/OFF
            - bit 2 is for AC ECO MODE ON/OFF
            - bit 3 is for MAX AC REAR ON/OFF
            - bit 4-7 is reserved
    */
    http::ac_compressor_eco_max = status;
    http::ac_modification_state = modi_state;
    http::ac_modifcation_reason = modi_reason;
    const std::shared_ptr<FsgIpv6> fsg = FsgIpv6::instance();
    if (fsg == nullptr) {
        std::cerr << "fsg is nullptr\n";
        return;
    }
    auto [data, len] = fsg->loadData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateMaster,
        fctId_t::BapFct_ClimateMaster_AC
    );
    if (status) {
        // on max & off eco
        data[0] |= (1 << 1); // on MAX mode
        data[0] &= ~(1 << 2); // off ECO mode
    } else {
        // off max & on eco
        data[0] |= (1 << 2); // on ECO mode
        data[0] &= ~(1 << 1); // off MAX mode
    }

    /* modifition state */
    if (modi_state) {
        // can change
        data[len-1] |= (1 << 0);
    } else {
        // can not change
        data[len-1] &= ~(1 << 0);
    }

    /* modifition reason */
    data[len-1] &= 0x0F;
    data[len-1] |= (uint8_t)(modi_reason << 4);

    (void)fsg->storeData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateMaster,
        fctId_t::BapFct_ClimateMaster_AC,
        {data, len}
    );
    fsg->write_ac_compressor_eco_max(data);
}

void BapParser::encode_temp_zl(const float32_t value,
                               const int32_t unit,
                               const bool modi_state,
                               const int32_t modi_reason)
{
    /*
        base on page 42 - 47 of document : BAP-FC_ClimateZone_P30DF7.17_V5.17.0_F.pdf
        - first byte is temperature value, range value from 0 - 255
        - second byte is unit type C/F
        - last byte is modification state/reason
    */
    http::zl_temp_value = value;
    http::zl_temp_unit = unit;
    http::zl_air_volume_modification_state = modi_state;
    http::zl_air_volume_modification_reason = modi_reason;
    const std::shared_ptr<FsgIpv6> fsg = FsgIpv6::instance();
    if (fsg == nullptr) {
        std::cerr << "fsg is nullptr\n";
        return;
    }
    auto [data, len] = fsg->loadData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_Temperature
    );
    const uint8_t temp_cel = static_cast<uint8_t>(std::round((value - 10.0f) / 0.1f));
    const uint8_t unit_type = (uint8_t)(unit);
    data[0] = temp_cel;
    data[1] = unit_type;

    /* modifition state */
    if (modi_state) {
        // can change
        data[len-1] |= (1 << 0);
    } else {
        // can not change
        data[len-1] &= ~(1 << 0);
    }

    /* modifition reason */
    data[len-1] &= 0x0F;
    data[len-1] |= (uint8_t)(modi_reason << 4);

    (void)fsg->storeData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_Temperature,
        {data, len}
    );
    fsg->write_hvac_temp_zl(data);
}

void BapParser::encode_temp_zr(const float32_t value,
                               const int32_t unit,
                               const bool modi_state,
                               const int32_t modi_reason)
{
    /*
        base on page 48 - 53 of document : BAP-FC_ClimateZone_P30DF7.17_V5.17.0_F.pdf
        first byte is temperature value, range value from 0 - 255
        second byte is unit type C/F
        Active step : will leave default, range value from 0 - 32
    */
    http::zr_temp_value = value;
    http::zr_temp_unit = unit;
    http::zr_air_volume_modification_state = modi_state;
    http::zr_air_volume_modification_reason = modi_reason;
    const std::shared_ptr<FsgIpv6> fsg = FsgIpv6::instance();
    if (fsg == nullptr) {
        std::cerr << "fsg is nullptr\n";
        return;
    }
    auto [data, len] = fsg->loadData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_Temperature
    );
    const uint8_t temp_cel = static_cast<uint8_t>(std::round((value - 10.0f) / 0.1f));
    const uint8_t unit_type = (uint8_t)(unit);
    data[0] = temp_cel;
    data[1] = unit_type;

    /* modifition state */
    if (modi_state) {
        // can change
        data[len-1] |= (1 << 0);
    } else {
        // can not change
        data[len-1] &= ~(1 << 0);
    }

    /* modifition reason */
    data[len-1] &= 0x0F;
    data[len-1] |= (uint8_t)(modi_reason << 4);

    (void)fsg->storeData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_Temperature,
        {data, len}
    );
    fsg->write_hvac_temp_zr(data);
}

void BapParser::encode_fan_speed_zl(const int32_t value,
                                    const bool modi_state,
                                    const int32_t modi_reason)
{
    /*
        base on page 54 - 59 of document : BAP-FC_ClimateZone_P30DF7.17_V5.17.0_F.pdf
        the first byte is for air volume and air volume regulated
        - the first 4 bits are for regulated (which we will not use it)
        - the second 4 bits are for manual volume change (what we will use)
        the 4'th byte is for modifition reason and state
        - the first 4 bits for state (only bit 0 used with 0 is can not modified, 1 is modify)
        - the second 4 bits for reason
    */
    http::zl_air_volume = value;
    http::zl_air_volume_modification_state = modi_state;
    http::zl_air_volume_modification_reason = modi_reason;
    const std::shared_ptr<FsgIpv6> fsg = FsgIpv6::instance();
    if (fsg == nullptr) {
        std::cerr << "fsg is nullptr\n";
        return;
    }
    auto [data, len] = fsg->loadData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_AirVolume
    );
    data[0] &= 0x0F;
    data[0] |= (value << 4);

    /* modifition state */
    if (modi_state) {
        // can change
        data[len-1] |= (1 << 0);
    } else {
        // can not change
        data[len-1] &= ~(1 << 0);
    }

    /* modifition reason */
    data[len-1] &= 0x0F;
    data[len-1] |= (uint8_t)(modi_reason << 4);

    (void)fsg->storeData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_AirVolume,
        {data, len}
    );
    fsg->write_hvac_fan_speed_zl(data);
}

void BapParser::encode_fan_speed_zr(const int32_t value,
                                    const bool modi_state,
                                    const int32_t modi_reason)
{
    /*
        base on page 60 - 65 of document : BAP-FC_ClimateZone_P30DF7.17_V5.17.0_F.pdf
        the first byte is for air volume and air volume regulated
        - the first 4 bits are for regulated (which we will not use it)
        - the second 4 bits are for manual volume change (what we will use)
    */
    http::zr_air_volume = value;
    http::zr_air_volume_modification_state = modi_state;
    http::zr_air_volume_modification_reason = modi_reason;
    const std::shared_ptr<FsgIpv6> fsg = FsgIpv6::instance();
    if (fsg == nullptr) {
        std::cerr << "fsg is nullptr\n";
        return;
    }
    auto [data, len] = fsg->loadData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_AirVolume
    );
    data[0] &= 0x0F;
    data[0] |= (value << 4);

    /* modifition state */
    if (modi_state) {
        // can change
        data[len-1] |= (1 << 0);
    } else {
        // can not change
        data[len-1] &= ~(1 << 0);
    }

    /* modifition reason */
    data[len-1] &= 0x0F;
    data[len-1] |= (uint8_t)(modi_reason << 4);

    (void)fsg->storeData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_AirVolume,
        {data, len}
    );
    fsg->write_hvac_fan_speed_zr(data);
}

void BapParser::encode_rvc(const bool status)
{
    (void)status;
}

void BapParser::encode_seat_climate_zl(const int32_t heat_val,
                                       const int32_t heat_state,
                                       const int32_t ventilation_val,
                                       const int32_t ventilation_state)
{
    http::zl_seat_climate_heat_value = heat_val;
    http::zl_seat_climate_heat_state = heat_state;
    http::zl_seat_climate_ventilation_value = ventilation_val;
    http::zl_seat_climate_ventilation_state = ventilation_state;
    std::cout << "seat climate zl : "
              << ", heat val : " << heat_val
              << ", heat state : " << heat_state
              << ", ventilation val : " << ventilation_val
              << ", ventilation state : " << ventilation_state << '\n';
    const std::shared_ptr<FsgIpv6> fsg = FsgIpv6::instance();
    if (fsg == nullptr) {
        std::cerr << "fsg is nullptr\n";
        return;
    }
    /*
        base on page 82 - 83 of document : BAP-FC_ClimateZone_P30DF7.17_V5.17.0_F.pdf
        - first byte for seat heater
            + upper nibble is heater state
            + lower nibble is heater value
        - second byte for seat ventilation
            + upper nibble is ventilation state
            + lower nibble is ventilation value
    */
    auto [data, len] = fsg->loadData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_SeatClimate
    );
    uint8_t heat = 0u;
    heat |= static_cast<uint8_t>((heat_val << 0));
    heat |= static_cast<uint8_t>((heat_state << 4));
    data[0] = heat;
    uint8_t ventilation = 0u;
    ventilation |= static_cast<uint8_t>((ventilation_val << 0));
    ventilation |= static_cast<uint8_t>((ventilation_state << 4));
    data[1] = ventilation;
    (void)fsg->storeData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_SeatClimate,
        {data, len}
    );
    std::cout << "DEBUG : heat : " << static_cast<int32_t>(data[0])
              << ", ventilation : " << static_cast<int32_t>(data[1]) << '\n';
    for (int32_t i = 0; i < (len + 6u - 1u) / 6u; i++) {
        auto it_start = data.begin() + (i * 6u);
        auto it_end = (it_start + 6u > data.end()) ? data.end() : (it_start + 6u);
        fsg->write_seat_climate_zl(std::vector<uint8_t>(it_start, it_end));
    }
}

void BapParser::encode_seat_climate_zr(const int32_t heat_val,
                                       const int32_t heat_state,
                                       const int32_t ventilation_val,
                                       const int32_t ventilation_state)
{
    http::zr_seat_climate_heat_value = heat_val;
    http::zr_seat_climate_heat_state = heat_state;
    http::zr_seat_climate_ventilation_value = ventilation_val;
    http::zr_seat_climate_ventilation_state = ventilation_state;
    const std::shared_ptr<FsgIpv6> fsg = FsgIpv6::instance();
    if (fsg == nullptr) {
        std::cerr << "fsg is nullptr\n";
        return;
    }
    /*
        base on page 90 - 91 of document : BAP-FC_ClimateZone_P30DF7.17_V5.17.0_F.pdf
        - first byte for seat heater
            + upper nibble is heater state
            + lower nibble is heater value
        - second byte for seat ventilation
            + upper nibble is ventilation state
            + lower nibble is ventilation value
    */
    auto [data, len] = fsg->loadData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_SeatClimate
    );
    uint8_t heat = 0u;
    heat |= static_cast<uint8_t>((heat_val << 0));
    heat |= static_cast<uint8_t>((heat_state << 4));
    data[0] = heat;
    uint8_t ventilation = 0u;
    ventilation |= static_cast<uint8_t>((ventilation_val << 0));
    ventilation |= static_cast<uint8_t>((ventilation_state << 4));
    data[1] = ventilation;
    (void)fsg->storeData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_SeatClimate,
        {data, len}
    );
    for (int32_t i = 0; i < (len + 6u - 1u) / 6u; i++) {
        auto it_start = data.begin() + (i * 6u);
        auto it_end = (it_start + 6u > data.end()) ? data.end() : (it_start + 6u);
        fsg->write_seat_climate_zr(std::vector<uint8_t>(it_start, it_end));
    }
}

void BapParser::encode_air_circulation_manual(const bool value)
{
    /*
        base on page 82 - 83 of document : BAP-FC_ClimateMaster_P31DF3.19_V1.19.0_F.pdf
        - first byte for manual circulation
            - first bit for set ON/OFF circulation
    */
    http::air_circulation_manual_state = value;
    const std::shared_ptr<FsgIpv6> fsg = FsgIpv6::instance();
    if (fsg == nullptr) {
        std::cerr << "fsg is nullptr\n";
        return;
    }
    auto [data, len] = fsg->loadData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateMaster,
        fctId_t::BapFct_ClimateMaster_AirCirculation
    );
    // reset first bit to zero for next update
    uint8_t set_val = data[0] & (uint8_t)(~(1 << 0));
    if (value) {
        // request cabin air
        set_val |= (1 << 0);
    } else {
        // request outside air
        // because we erase bit 0 before apply so do nothing in this case
    }
    (void)fsg->storeData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateMaster,
        fctId_t::BapFct_ClimateMaster_AirCirculation,
        {data, len}
    );
    fsg->write_air_circ_manual(data);
}

void BapParser::encode_air_distribution_zl(const int32_t value)
{
    /*
        base on page 73 of document : BAP-FC_ClimateZone_P30DF7.17_V5.17.0_F.pdf
        - first byte contain up and body
            + upper nibble is up
            + lower nibble is body
        - second byte and upper nibble is footwell
    */
    http::zl_air_distribution_state = value;
    const std::shared_ptr<FsgIpv6> fsg = FsgIpv6::instance();
    if (fsg == nullptr) {
        std::cerr << "fsg is nullptr\n";
        return;
    }
    auto [data, len] = fsg->loadData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_AirDistribution
    );
    data[0] = 0u;
    data[1] &= 0x0Fu;
    switch (value) {
        case static_cast<int32_t>(AirDistribute_t::UP):
        {
            data[0] |= (12 << 4);
            break;
        }
        case static_cast<int32_t>(AirDistribute_t::BODY):
        {
            data[0] |= (12 << 0);
            break;
        }
        case static_cast<int32_t>(AirDistribute_t::FOOTWELL):
        {
            data[1] |= (12 << 4);
            break;
        }
        default:
        {
            std::cerr << "Unsupported direction : " << value << '\n';
            break;
        }
    }
    const int32_t ret = fsg->storeData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_AirDistribution,
        {data, len}
    );
    fsg->write_air_dist_zl(data);
}

void BapParser::encode_air_distribution_zr(const int32_t value)
{
    /*
        base on page 73 of document : BAP-FC_ClimateZone_P30DF7.17_V5.17.0_F.pdf
        - first byte contain up and body
            + upper nibble is up
            + lower nibble is body
        - second byte and upper nibble is footwell
    */
    http::zr_air_distribution_state = value;
    const std::shared_ptr<FsgIpv6> fsg = FsgIpv6::instance();
    if (fsg == nullptr) {
        std::cerr << "fsg is nullptr\n";
        return;
    }
    auto [data, len] = fsg->loadData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_AirDistribution
    );
    data[0] = 0u;
    data[1] &= 0x0Fu;
    switch (value) {
        case static_cast<int32_t>(AirDistribute_t::UP):
        {
            data[0] |= (12 << 4);
            break;
        }
        case static_cast<int32_t>(AirDistribute_t::BODY):
        {
            data[0] |= (12 << 0);
            break;
        }
        case static_cast<int32_t>(AirDistribute_t::FOOTWELL):
        {
            data[1] |= (12 << 4);
            break;
        }
        default:
        {
            std::cerr << "Unsupported direction : " << value << '\n';
            break;
        }
    }
    const int32_t ret = fsg->storeData<std::vector<uint8_t>>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_AirDistribution,
        {data, len}
    );
    fsg->write_air_dist_zr(data);
}
