#ifndef __FSG_LOG_HPP__
#define __FSG_LOG_HPP__

#include <iostream>
#include <sstream>
#include <stdio.h>
#if !defined(_WIN32) || defined(__CYGWIN__)
#include <syslog.h>
#endif
#include <cstdio>
#include <ctime>
#include <string.h>

#ifndef FSG_SERVICE_NAME
#define FSG_SERVICE_NAME "car-interface-function"
#endif // FSG_SERVICE_NAME

static char context_str[] = FSG_SERVICE_NAME;

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

class FsgLogMessage {
public:
    enum Level { DEBUG, INFO, WARN, ERR, FATAL };
    FsgLogMessage(const Level log_level, const char* file_path, const char* pretty_fn)
                : m_level(log_level)
    {
        m_ss << "[" << context_str << "]"
             << "[" << _cleanFileName(file_path) << "]"
             << "[" << _cleanFunctionName(pretty_fn) << "]  ";
    }

    template<typename T>
    FsgLogMessage& operator<<(const T& val)
    {
        m_ss << val;
        return *this;
    }

    ~FsgLogMessage(void)
    {
        std::string msg = m_ss.str();
        const char* level_str = "UNKNOWN";
        switch (m_level)
        {
            case Level::DEBUG:
            {
                level_str = "DEBUG";
                std::fprintf(stdout, "%s %-5s %s\n", nm_log_time(), level_str, msg.c_str());
                break;
            }
            case Level::INFO:
            {
                level_str = "INFO";
                std::fprintf(stdout, "%s %-5s %s\n", nm_log_time(), level_str, msg.c_str());
                break;
            }
            case Level::WARN:
            {
                level_str = "WARN";
                std::fprintf(stdout, "%s %-5s %s\n", nm_log_time(), level_str, msg.c_str());
                break;
            }
            case Level::ERR:
            {
                level_str = "ERROR";
                std::fprintf(stdout, "%s %-5s %s\n", nm_log_time(), level_str, msg.c_str());
                break;
            }
            case Level::FATAL:
            {
                level_str = "FATAL";
                std::fprintf(stdout, "%s %-5s %s\n", nm_log_time(), level_str, msg.c_str());
                break;
            }
            default:
            {
                break;
            }
        }
        std::fflush(stdout);
    }

private:
    std::ostringstream m_ss;
    Level m_level;
    inline static std::string _cleanFunctionName(const std::string& pretty_fn)
    {
        const size_t end_p = pretty_fn.find('(');
        if (end_p == std::string::npos) return pretty_fn;
        size_t begin_p = pretty_fn.rfind(' ', end_p);
        if (begin_p == std::string::npos)
            begin_p = 0u;
        else
            begin_p += 1u;

        while (begin_p < end_p && (pretty_fn[begin_p] == '*' || pretty_fn[begin_p] == '&')) {
            begin_p++;
        }
        return pretty_fn.substr(begin_p, end_p - begin_p);
    }

    inline static std::string _cleanFileName(const std::string& file_path)
    {
        size_t last_slash = file_path.find_last_of("/\\");
        if (last_slash == std::string::npos) {
            return file_path;
        }
        return file_path.substr(last_slash + 1);
    }
};

#define LOG_DEBUG   FsgLogMessage(FsgLogMessage::Level::DEBUG,  __FILE__, __PRETTY_FUNCTION__)
#define LOG_INFO    FsgLogMessage(FsgLogMessage::Level::INFO,   __FILE__, __PRETTY_FUNCTION__)
#define LOG_WARN    FsgLogMessage(FsgLogMessage::Level::WARN,   __FILE__, __PRETTY_FUNCTION__)
#define LOG_ERR     FsgLogMessage(FsgLogMessage::Level::ERR,    __FILE__, __PRETTY_FUNCTION__)
#define LOG_FATAL   FsgLogMessage(FsgLogMessage::Level::FATAL,  __FILE__, __PRETTY_FUNCTION__)

#endif // __FSG_LOG_HPP__
