#include "HttpRequestHandler.hpp"
#include "FsgType.hpp"
#include "FsgDefaultValue.hpp"
#include "BapParser.hpp"

#define PIPE_NAME L"\\\\.\\pipe\\MyTerminalPipe"
#define BUFFER_SIZE 1024

HttpRequestHandler::HttpRequestHandler(void)
{
    m_startStatus.store(false);
}

HttpRequestHandler::~HttpRequestHandler(void)
{

}

void HttpRequestHandler::start(void)
{
    using httpReq = http::HttpRequestType_t;
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "=========== establish server com pipe ======================\n";

    const std::shared_ptr<BapParser> parser = BapParser::instance();
    if (parser == nullptr) {
        std::cerr << "[HTTP] parser is nullptr\n";
        return;
    }
    m_startStatus.store(true);
    m_handlerThread = std::thread([&](void) -> void {
        while (m_startStatus.load()) {
            HANDLE hPipe = CreateNamedPipeW(
                PIPE_NAME,
                PIPE_ACCESS_INBOUND | FILE_FLAG_OVERLAPPED,
                PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
                PIPE_UNLIMITED_INSTANCES,
                BUFFER_SIZE,
                BUFFER_SIZE,
                0,
                NULL
            );

            if (hPipe == INVALID_HANDLE_VALUE) {
                std::wcerr << L"Failed to create pipe err: " << GetLastError() << std::endl;
                Sleep(2000);
                continue;
            }

            OVERLAPPED olConnect = { 0 };
            olConnect.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

            if (olConnect.hEvent == NULL) {
                CloseHandle(hPipe);
                continue;
            }

            BOOL fConnect = ConnectNamedPipe(hPipe, &olConnect);
            
            if (!fConnect) {
                DWORD err = GetLastError();
                if (err == ERROR_IO_PENDING) {
                    WaitForSingleObject(olConnect.hEvent, INFINITE);
                } else if (err != ERROR_PIPE_CONNECTED) {
                    CloseHandle(olConnect.hEvent);
                    CloseHandle(hPipe);
                    continue;
                }
            }

            char buffer[BUFFER_SIZE];
            OVERLAPPED olRead = { 0 };
            olRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

            DWORD totalBytesRead = 0;
            DWORD requiredSize = 0;
            uint8_t requestType = 0u;
            bool isValid = true;
            bool hasExtractedType = false;

            std::cout << "[HTTP] On receive message from GET/POST\n";

            while (true) {
                DWORD bytesRead = 0;
                ResetEvent(olRead.hEvent);
                
                BOOL fRead = ReadFile(
                    hPipe,
                    buffer + totalBytesRead,
                    BUFFER_SIZE - 1 - totalBytesRead,
                    &bytesRead,
                    &olRead
                );

                if (!fRead && GetLastError() == ERROR_IO_PENDING) {
                    WaitForSingleObject(olRead.hEvent, INFINITE);
                    GetOverlappedResult(hPipe, &olRead, &bytesRead, FALSE);
                }

                if (bytesRead > 0) {
                    totalBytesRead += bytesRead;

                    if (!hasExtractedType && totalBytesRead >= sizeof(uint8_t)) {
                        std::memcpy(&requestType, buffer, sizeof(uint8_t));
                        hasExtractedType = true;
                    }

                    if (hasExtractedType) {
                        switch (requestType)
                        {
                            case static_cast<uint8_t>(httpReq::MODIFY_HVAC_STATUS):
                            {
                                // 1 byte ID + 1 byte for cmd
                                requiredSize = 2u;
                                break;
                            }
                            case static_cast<uint8_t>(httpReq::MODIFY_AC_COMPRESSOR_STATUS):
                            {
                                /*
                                    1 byte for ID
                                    1 byte for ac compressor status
                                    1 byte for ac compressor modification state
                                    1 byte for ac compressor modification reason
                                */
                                requiredSize = 4u;
                                break;
                            }
                            case static_cast<uint8_t>(httpReq::MODIFY_AC_COMPRESSOR_ECO_MAX):
                            {
                                /*
                                    1 byte for ID
                                    1 byte for ac compressor eco max cmd
                                    1 byte for ac compressor modification state
                                    1 byte for ac compressor modification reason
                                */
                                requiredSize = 4u;
                                break;
                            }
                            case static_cast<uint8_t>(httpReq::MODIFY_HVAC_TEMP_ZL):
                            {
                                /*
                                    1 byte for ID
                                    1 byte for temp
                                    1 byte for unit
                                    1 byte for ac compressor modification state
                                    1 byte for ac compressor modification reason
                                */
                                requiredSize = 5u;
                                break;
                            }
                            case static_cast<uint8_t>(httpReq::MODIFY_HVAC_TEMP_ZR):
                            {
                                /*
                                    1 byte for ID
                                    1 byte for temp
                                    1 byte for unit
                                    1 byte for ac compressor modification state
                                    1 byte for ac compressor modification reason
                                */
                                requiredSize = 5u;
                                break;
                            }
                            case static_cast<uint8_t>(httpReq::MODIFY_HVAC_FAN_SPEED_ZL):
                            {
                                /*
                                    1 byte for ID
                                    1 byte for air volume
                                    1 byte for ac compressor modification state
                                    1 byte for ac compressor modification reason
                                */
                                requiredSize = 4u;
                                break;
                            }
                            case static_cast<uint8_t>(httpReq::MODIFY_HVAC_FAN_SPEED_ZR):
                            {
                                /*
                                    1 byte for ID
                                    1 byte for air volume
                                    1 byte for ac compressor modification state
                                    1 byte for ac compressor modification reason
                                */
                                requiredSize = 4u;
                                break;
                            }
                            case static_cast<uint8_t>(httpReq::MODIFY_RVC):
                            {
                                // 1 byte ID + rvc cmd
                                requiredSize = 2u;
                                break;
                            }
                            case static_cast<uint8_t>(httpReq::MODIFY_SEAT_CLIMATE_ZL):
                            {
                                /*
                                    1 byte for ID
                                    1 byte for seat climate heat state
                                    1 byte for seat climate heat value
                                    1 byte for seat climate ventilation state
                                    1 byte for seat climate ventilation value
                                */
                                requiredSize = 5u;
                                break;
                            }
                            case static_cast<uint8_t>(httpReq::MODIFY_SEAT_CLIMATE_ZR):
                            {
                                /*
                                    1 byte for ID
                                    1 byte for seat climate heat state
                                    1 byte for seat climate heat value
                                    1 byte for seat climate ventilation state
                                    1 byte for seat climate ventilation value
                                */
                                requiredSize = 5u;
                                break;
                            }
                            case static_cast<uint8_t>(httpReq::MODIFY_AIR_CIRC_MANUAL):
                            {
                                /*
                                    1 byte for ID
                                    1 byte for air circulation manual cmd
                                */
                                requiredSize = 2u;
                                break;
                            }
                            case static_cast<uint8_t>(httpReq::MODIFY_AIR_DIST_ZL):
                            {
                                /*
                                    1 byte for ID
                                    1 byte for air distribution state
                                */
                                requiredSize = 2u;
                                break;
                            }
                            case static_cast<uint8_t>(httpReq::MODIFY_AIR_DIST_ZR):
                            {
                                /*
                                    1 byte for ID
                                    1 byte for air distribution state
                                */
                                requiredSize = 2u;
                                break;
                            }
                            default:
                            {
                                std::wcerr << "Type is not supported, type : "
                                           << static_cast<int32_t>(requestType) << '\n';
                                isValid = false;
                                break;
                            }
                        }
                    }

                    if (!isValid) break;

                    if (requiredSize > 0 && totalBytesRead >= requiredSize) {
                        std::cout << "[HTTP] request size matched !!! (Read: "
                                  << totalBytesRead << " bytes)\n";
                        break;
                    }
                } else {
                    isValid = false; 
                    break;
                }
            }

            if (!isValid) {
                std::cerr << "[HTTP] request is not valid\n";
                continue;
            }

            if (totalBytesRead < requiredSize) {
                std::cerr << "[HTTP] request is not match for type : "
                          << static_cast<int32_t>(requestType) << '\n';\
                continue;
            }

            switch (requestType)
            {
                using httpReq = http::HttpRequestType_t;
                case static_cast<uint8_t>(httpReq::MODIFY_HVAC_STATUS):
                {
                    uint8_t raw_bool_val = 0;
                    std::memcpy(&raw_bool_val, buffer + 1, sizeof(uint8_t)); 
                    const bool power_status = (raw_bool_val != 0u);
                    parser->encode_hvac_power(power_status);
                    break;
                }
                case static_cast<uint8_t>(httpReq::MODIFY_AC_COMPRESSOR_STATUS):
                {
                    /*
                        1 byte for ID
                        1 byte for ac compressor status
                        1 byte for ac compressor modification state
                        1 byte for ac compressor modification reason
                    */
                    uint8_t status_temp = 0u;
                    std::memcpy(&status_temp, buffer+1, sizeof(uint8_t));
                    const bool status = (status_temp != 0u);
                    uint8_t modi_state_temp = 0u;
                    std::memcpy(&modi_state_temp, buffer+2, sizeof(uint8_t));
                    const bool modi_state = (modi_state_temp != 0u);
                    uint8_t modi_reason_temp = 0u;
                    std::memcpy(&modi_reason_temp, buffer+3, sizeof(uint8_t));
                    const int32_t modi_reason = static_cast<int32_t>(modi_reason_temp);
                    parser->encode_ac_compressor_status(status, modi_state, modi_reason);
                    break;
                }
                case static_cast<uint8_t>(httpReq::MODIFY_AC_COMPRESSOR_ECO_MAX):
                {
                    /*
                        1 byte for ID
                        1 byte for ac compressor eco max cmd
                        1 byte for ac compressor modification state
                        1 byte for ac compressor modification reason
                    */
                    uint8_t mode_temp = 0u;
                    std::memcpy(&mode_temp, buffer+1, sizeof(uint8_t));
                    const bool mode = (mode_temp != 0u);
                    uint8_t modi_state_temp = 0u;
                    std::memcpy(&modi_state_temp, buffer+2, sizeof(uint8_t));
                    const bool modi_state = (modi_state_temp != 0u);
                    uint8_t modi_reason_temp = 0u;
                    std::memcpy(&modi_reason_temp, buffer+3, sizeof(uint8_t));
                    const int32_t modi_reason = static_cast<int32_t>(modi_reason_temp);
                    parser->encode_ac_compressor_status(mode, modi_state, modi_reason);
                    break;
                }
                case static_cast<uint8_t>(httpReq::MODIFY_HVAC_TEMP_ZL):
                {
                    /*
                        1 byte for ID
                        4 byte for temp
                        1 byte for unit
                        1 byte for ac compressor modification state
                        1 byte for ac compressor modification reason
                    */
                    float32_t temperature = 0.0f;
                    std::memcpy(&temperature, buffer+1, sizeof(float32_t));
                    uint8_t unit_temp = 0u;
                    std::memcpy(&unit_temp, buffer+5, sizeof(uint8_t));
                    const int32_t unit = static_cast<int32_t>(unit_temp);
                    uint8_t modi_state_temp = 0u;
                    std::memcpy(&modi_state_temp, buffer+6, sizeof(uint8_t));
                    const bool modi_state = (modi_state_temp != 0u);
                    uint8_t modi_reason_temp = 0u;
                    std::memcpy(&modi_reason_temp, buffer+7, sizeof(uint8_t));
                    const int32_t modi_reason = static_cast<int32_t>(modi_reason_temp);
                    parser->encode_temp_zl(temperature, unit, modi_state, modi_reason);
                    break;
                }
                case static_cast<uint8_t>(httpReq::MODIFY_HVAC_TEMP_ZR):
                {
                    /*
                        1 byte for ID
                        4 byte for temp
                        1 byte for unit
                        1 byte for ac compressor modification state
                        1 byte for ac compressor modification reason
                    */
                    float32_t temperature = 0.0f;
                    std::memcpy(&temperature, buffer+1, sizeof(float32_t));
                    uint8_t unit_temp = 0u;
                    std::memcpy(&unit_temp, buffer+5, sizeof(uint8_t));
                    const int32_t unit = static_cast<int32_t>(unit_temp);
                    uint8_t modi_state_temp = 0u;
                    std::memcpy(&modi_state_temp, buffer+6, sizeof(uint8_t));
                    const bool modi_state = (modi_state_temp != 0u);
                    uint8_t modi_reason_temp = 0u;
                    std::memcpy(&modi_reason_temp, buffer+7, sizeof(uint8_t));
                    const int32_t modi_reason = static_cast<int32_t>(modi_reason_temp);
                    parser->encode_temp_zr(temperature, unit, modi_state, modi_reason);
                    break;
                }
                case static_cast<uint8_t>(httpReq::MODIFY_HVAC_FAN_SPEED_ZL):
                {
                    /*
                        1 byte for ID
                        1 byte for air volume
                        1 byte for ac compressor modification state
                        1 byte for ac compressor modification reason
                    */
                    uint8_t volume_temp = 0u;
                    std::memcpy(&volume_temp, buffer+1, sizeof(uint8_t));
                    const int32_t volume = static_cast<int32_t>(volume_temp);
                    uint8_t modi_state_temp = 0u;
                    std::memcpy(&modi_state_temp, buffer+2, sizeof(uint8_t));
                    const bool modi_state = (modi_state_temp != 0u);
                    uint8_t modi_reason_temp = 0u;
                    std::memcpy(&modi_reason_temp, buffer+3, sizeof(uint8_t));
                    const int32_t modi_reason = static_cast<int32_t>(modi_reason_temp);
                    parser->encode_fan_speed_zl(volume, modi_state, modi_reason);
                    break;
                }
                case static_cast<uint8_t>(httpReq::MODIFY_HVAC_FAN_SPEED_ZR):
                {
                    /*
                        1 byte for ID
                        1 byte for air volume
                        1 byte for ac compressor modification state
                        1 byte for ac compressor modification reason
                    */
                    uint8_t volume_temp = 0u;
                    std::memcpy(&volume_temp, buffer+1, sizeof(uint8_t));
                    const int32_t volume = static_cast<int32_t>(volume_temp);
                    uint8_t modi_state_temp = 0u;
                    std::memcpy(&modi_state_temp, buffer+2, sizeof(uint8_t));
                    const bool modi_state = (modi_state_temp != 0u);
                    uint8_t modi_reason_temp = 0u;
                    std::memcpy(&modi_reason_temp, buffer+3, sizeof(uint8_t));
                    const int32_t modi_reason = static_cast<int32_t>(modi_reason_temp);
                    parser->encode_fan_speed_zr(volume, modi_state, modi_reason);
                    break;
                }
                case static_cast<uint8_t>(httpReq::MODIFY_RVC):
                {
                    // 1 byte ID + rvc cmd
                    requiredSize = 2u;
                    std::cout << "Not yet support\n";
                    break;
                }
                case static_cast<uint8_t>(httpReq::MODIFY_SEAT_CLIMATE_ZL):
                {
                    /*
                        1 byte for ID
                        1 byte for seat climate heat state
                        1 byte for seat climate heat value
                        1 byte for seat climate ventilation state
                        1 byte for seat climate ventilation value
                    */
                    uint8_t heat_state_temp = 0u;
                    std::memcpy(&heat_state_temp, buffer+1, sizeof(uint8_t));
                    const int32_t heat_state = static_cast<int32_t>(heat_state_temp);
                    uint8_t heat_value_temp = 0u;
                    std::memcpy(&heat_value_temp, buffer+2, sizeof(uint8_t));
                    const int32_t heat_value = static_cast<int32_t>(heat_value_temp);
                    uint8_t ventilation_state_temp = 0u;
                    std::memcpy(&ventilation_state_temp, buffer+3, sizeof(uint8_t));
                    const int32_t ventilation_state = static_cast<int32_t>(ventilation_state_temp);
                    uint8_t ventilation_value_temp = 0u;
                    std::memcpy(&ventilation_value_temp, buffer+4, sizeof(uint8_t));
                    const int32_t ventilation_value = static_cast<int32_t>(ventilation_value_temp);
                    parser->encode_seat_climate_zl(
                        heat_value,
                        heat_state,
                        ventilation_value,
                        ventilation_state
                    );
                    break;
                }
                case static_cast<uint8_t>(httpReq::MODIFY_SEAT_CLIMATE_ZR):
                {
                    /*
                        1 byte for ID
                        1 byte for seat climate heat state
                        1 byte for seat climate heat value
                        1 byte for seat climate ventilation state
                        1 byte for seat climate ventilation value
                    */
                    uint8_t heat_state_temp = 0u;
                    std::memcpy(&heat_state_temp, buffer+1, sizeof(uint8_t));
                    const int32_t heat_state = static_cast<int32_t>(heat_state_temp);
                    uint8_t heat_value_temp = 0u;
                    std::memcpy(&heat_value_temp, buffer+2, sizeof(uint8_t));
                    const int32_t heat_value = static_cast<int32_t>(heat_value_temp);
                    uint8_t ventilation_state_temp = 0u;
                    std::memcpy(&ventilation_state_temp, buffer+3, sizeof(uint8_t));
                    const int32_t ventilation_state = static_cast<int32_t>(ventilation_state_temp);
                    uint8_t ventilation_value_temp = 0u;
                    std::memcpy(&ventilation_value_temp, buffer+4, sizeof(uint8_t));
                    const int32_t ventilation_value = static_cast<int32_t>(ventilation_value_temp);
                    parser->encode_seat_climate_zr(
                        heat_value,
                        heat_state,
                        ventilation_value,
                        ventilation_state
                    );
                    break;
                }
                case static_cast<uint8_t>(httpReq::MODIFY_AIR_CIRC_MANUAL):
                {
                    /*
                        1 byte for ID
                        1 byte for air circulation manual cmd
                    */
                    uint8_t circ_manual_temp = 0u;
                    std::memcpy(&circ_manual_temp, buffer+1, sizeof(uint8_t));
                    const bool circ_manual = (circ_manual_temp != 0u);
                    parser->encode_air_circulation_manual(circ_manual);
                    break;
                }
                case static_cast<uint8_t>(httpReq::MODIFY_AIR_DIST_ZL):
                {
                    /*
                        1 byte for ID
                        1 byte for air distribution state
                    */
                    uint8_t distribution_state_temp = 0u;
                    std::memcpy(&distribution_state_temp, buffer+1, sizeof(uint8_t));
                    const int32_t distribution_state = static_cast<int32_t>(
                        distribution_state_temp
                    );
                    parser->encode_air_distribution_zl(distribution_state);
                    break;
                }
                case static_cast<uint8_t>(httpReq::MODIFY_AIR_DIST_ZR):
                {
                    /*
                        1 byte for ID
                        1 byte for air distribution state
                    */
                    uint8_t distribution_state_temp = 0u;
                    std::memcpy(&distribution_state_temp, buffer+1, sizeof(uint8_t));
                    const int32_t distribution_state = static_cast<int32_t>(
                        distribution_state_temp
                    );
                    parser->encode_air_distribution_zr(distribution_state);
                    break;
                }
                default:
                    break;
            }

            CloseHandle(olRead.hEvent);
            DisconnectNamedPipe(hPipe);
            CloseHandle(hPipe);
            CloseHandle(olConnect.hEvent);
        }
    });
    m_handlerThread.detach();
}

void HttpRequestHandler::stop(void)
{
    m_startStatus.store(false);
    if (m_handlerThread.joinable()) {
        m_handlerThread.join();
    }
}
