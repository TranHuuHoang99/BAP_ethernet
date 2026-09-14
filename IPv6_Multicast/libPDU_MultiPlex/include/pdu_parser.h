#ifndef __PDU_PARSER_H__
#define __PDU_PARSER_H__
#include <vector>
#include <stdint.h>
#include <cstddef>
#include "pdu.h"

class PDUParser {
public:
    PDUParser();
    ~PDUParser();
    static std::vector<PDU> parse(const uint8_t* data, size_t length);
};

#endif // __PDU_PARSER_H__
