#ifndef __GENERAL_TRANSFER_SIMULATION__
#define  __GENERAL_TRANSFER_SIMULATION__

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#if defined(__CYGWIN__) || defined(WIN32)
    #include <windows.h>
#endif // defined(__CYGWIN__) || defined(WIN32)

class GTSimulation {
public:
    GTSimulation(const std::string exe_path);
    ~GTSimulation(void);

    void startGeneralTransfer(void);
private:
    std::string m_exePath;
};

#endif // __GENERAL_TRANSFER_SIMULATION__
