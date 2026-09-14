#include <iostream>
#include <thread>
#include "FsgIpv6.hpp"

int main(void)
{
    const int32_t ret_init = FsgIpv6::instance()->init();
    if (ret_init < 0) {
        std::cerr << "[SERVER] Failed to initialize FSG IPv6 multicast server\n";
        return 1;
    }

    FsgIpv6::instance()->start();

    return 0;
}
