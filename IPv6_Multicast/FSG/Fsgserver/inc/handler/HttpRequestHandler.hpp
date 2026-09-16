#ifndef __HTTP_REQUEST_HANDLER_HPP__
#define __HTTP_REQUEST_HANDLER_HPP__

#include "FsgType.hpp"
#include <windows.h>

class HttpRequestHandler {
public:
    HttpRequestHandler(void);
    ~HttpRequestHandler(void);

    void start(void);
    void stop(void);

private:
    std::atomic_bool m_startStatus;
    std::thread m_handlerThread;
};

#endif // __HTTP_REQUEST_HANDLER_HPP__
