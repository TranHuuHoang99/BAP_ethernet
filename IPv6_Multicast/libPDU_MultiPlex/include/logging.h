// Unified logging for Android (logcat) and host (stdout)
#pragma once
#if defined(__ANDROID__)
#include <android/log.h>
#include <sys/system_properties.h>
#include <cstring>
namespace pdu_log {
class LogControl {
public:
    static LogControl& getInstance() {
        static LogControl instance;
        return instance;
    }
    bool isLogEnabled() const {
        char value[PROP_VALUE_MAX] = {0};
        // persist.vendor.pdu.log.enable (default: 0 - disabled)
        __system_property_get("persist.vendor.pdu.log.enable", value);
        return (strcmp(value, "1") == 0);
    }
private:
    LogControl() = default;
};
} // namespace pdu_log
#define LOG_PRI(priority, fmt, ...) __android_log_print(priority, "PDU", "%s: " fmt, __FUNCTION__, ##__VA_ARGS__)
#ifdef UNIT_TEST
#define LOGD(fmt, ...) do { LOG_PRI(ANDROID_LOG_DEBUG, fmt, ##__VA_ARGS__); } while(0)
#define LOGI(fmt, ...) do { LOG_PRI(ANDROID_LOG_INFO, fmt, ##__VA_ARGS__); } while(0)
#else
#define LOGD(fmt, ...) \
    do { if (pdu_log::LogControl::getInstance().isLogEnabled()) \
            LOG_PRI(ANDROID_LOG_DEBUG, fmt, ##__VA_ARGS__); } while(0)

#define LOGI(fmt, ...) \
    do { if (pdu_log::LogControl::getInstance().isLogEnabled()) \
            LOG_PRI(ANDROID_LOG_INFO, fmt, ##__VA_ARGS__); } while(0)
#endif
#define LOGW(fmt, ...) LOG_PRI(ANDROID_LOG_WARN, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) LOG_PRI(ANDROID_LOG_ERROR, fmt, ##__VA_ARGS__)
#else
#include <cstdio>
#include <ctime>
inline const char* nm_log_time() {
    static char buf[32];
    std::time_t t = std::time(nullptr);
    std::tm tm;
#if defined(_WIN32) && !defined(__CYGWIN__)
    localtime_s(&tm, &t);           // Windows CRT: note reversed argument order
#else
    localtime_r(&t, &tm);
#endif
    std::snprintf(buf,sizeof(buf),"%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
    return buf;
}

#if 0
#define LOG_BASE(level, fmt, ...) std::fprintf(stdout, "%s %-5s %-20s: " fmt "\n", nm_log_time(), level, __FILE__, ##__VA_ARGS__)
#else
#define LOG_BASE(level, fmt, ...)
#endif // 1

#define LOGD(fmt, ...) LOG_BASE("DEBUG", fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) LOG_BASE("INFO",  fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) LOG_BASE("WARN",  fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) LOG_BASE("ERROR", fmt, ##__VA_ARGS__)
#endif
