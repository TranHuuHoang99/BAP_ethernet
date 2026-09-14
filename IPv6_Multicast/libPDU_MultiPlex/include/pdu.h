#ifndef __PDU_H__
#define __PDU_H__
#include <stdint.h>
#include <vector>

struct PDU {
    uint32_t message_id;
    uint32_t length;
    std::vector<uint8_t> payload;
};

const size_t PDU_HEADER_SIZE = sizeof(uint32_t) * 2;

#endif // __PDU_H__
