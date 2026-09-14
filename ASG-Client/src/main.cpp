#include <iostream>
#include "ASGManager.hpp"
#include <thread>

int main(void)
{
    const int32_t ret_init = ASGManager::instance()->init();
    if (ret_init < 0) {
        std::cerr << "[CLIENT] Failed to initialize ASG client\n";
        return 1;
    }

    ASGManager::instance()->start();

    return 0;
}
