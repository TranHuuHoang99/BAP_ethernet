#include <iostream>
#include "FSGManager.hpp"
#include <thread>

int main(void)
{
    const int32_t ret_init = FSGManager::instance()->init();
    if (ret_init < 0) {
        std::cerr << "[SERVER] Failed to initialize FSG server\n";
        return 1;
    }

    FSGManager::instance()->start();

    return 0;
}
