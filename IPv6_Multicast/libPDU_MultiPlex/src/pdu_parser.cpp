#include "pdu_parser.h"
#include "logging.h"

#include <cstring>
#include "sys_endian.h"

PDUParser::PDUParser() {}
PDUParser::~PDUParser() {}

/**
 * @brief Parse raw data into a vector of PDUs.
 * 
 * This function takes a byte array and its length, and parses it into
 * individual PDUs based on the defined PDU structure.
 * 
 * @param data Pointer to the raw byte array.
 * @param length Length of the byte array.
 * @return A vector of parsed PDUs.
 */
std::vector<PDU> PDUParser::parse(const uint8_t* data, size_t length) {
    std::vector<PDU> pdus;
    size_t offset = 0;
    LOGD("PDUParser parse length=%zu", length);
    while (offset + 8 <= length) { // Ensure there's enough data for header
        PDU pdu;
        std::memcpy(&pdu.message_id, data + offset, 4);
        std::memcpy(&pdu.length, data + offset + 4, 4);
        offset += 8;

        pdu.message_id = be32_to_host(pdu.message_id);
        pdu.length = be32_to_host(pdu.length);

        if (offset + pdu.length > length) {
            LOGW("PDUParser truncated id=%u claimed=%u remaining=%zu", pdu.message_id, pdu.length, length - offset);
            return std::vector<PDU>(); // Return empty vector on error
        }
        pdu.payload.resize(pdu.length);
        std::memcpy(pdu.payload.data(), data + offset, pdu.length);
        offset += pdu.length;
        pdus.push_back(pdu);
        LOGD("PDUParser one id=%u len=%u", pdu.message_id, pdu.length);
    }
    LOGD("PDUParser done total=%zu", pdus.size());
    return pdus;
}
