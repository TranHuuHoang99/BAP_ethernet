#include "GTSimulation.hpp"

GTSimulation::GTSimulation(const std::string exe_path)
                    : m_exePath(exe_path)
{
    std::cout << "[GTSIMULATION] intialize general transfer\n";
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    
    std::string commandLine;
    try {
        commandLine = exe_path + " --ethernet-debug";
    } catch (std::length_error& err) {
        std::cerr << "[GTSIMULATION] failed to create command, err : " << err.what() << '\n';
    } catch (std::bad_alloc& err) {
        std::cerr << "[GTSIMULATION] failed to create command, err : " << err.what() << '\n';
    }
    
    BOOL success = CreateProcessA(
        nullptr,
        &commandLine[0],
        nullptr, nullptr, FALSE,
        CREATE_NEW_CONSOLE,
        nullptr, nullptr, &si, &pi
    );

    if (success) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        std::cerr << "[GTSIMULATION][ERROR] can not folk new process\n";
    }
}

GTSimulation::~GTSimulation(void)
{
    std::cout << "[GTSIMULATION] destroyed general Simulation object\n";
}

void GTSimulation::startGeneralTransfer(void)
{
    std::cout << "[GTSIMULATION] start general transfer\n";
    std::string command;
    int32_t fctId;
    while (true) {
        std::cout << "[GTSIMULATION] Type your command : ";
        std::getline(std::cin, command);

        if (command == "exit") {
            std::cout << "[GTSIMULATION] escape general transfer Simulation\n";
            break;
        }

        if (command != "get" && command != "set") {
            std::cerr << "[GTSIMULATION] Invalid command\n";
            break;
        }
        std::cout << "[GTSIMULATION] Enter function ID (fctId): ";
        std::cin >> fctId;
    }
}
