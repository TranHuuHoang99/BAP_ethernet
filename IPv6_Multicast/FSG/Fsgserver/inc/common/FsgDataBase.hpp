#ifndef __FSG_DATA_BASE_HPP__
#define __FSG_DATA_BASE_HPP__

#include <iostream>
#include <cstdint>
#include <map>
#include <any>
#include <functional>
#include <memory>
#include <optional>
#include <mutex>
#include <typeindex>
#include <type_traits>
#include "fsg_log.hpp"

extern "C" {
#include "bap_defines.h"
} // extern "C"

template<typename T>
struct DataType {
    T data;
    uint32_t len;
};

struct DataBase {
    std::mutex mt_loader;
    DataBase(void) = default;
    ~DataBase(void) = default;
    std::map<lsgId_t, std::map<fctId_t, std::any>> database;

    template<typename T>
    int32_t insert(const lsgId_t lsgId, const fctId_t fctId, DataType<T> data)
    {
        auto it_lsg = database.find(lsgId);
        if (it_lsg != database.end() && it_lsg->second.find(fctId) != it_lsg->second.end()) {
            LOG_DEBUG << "fctId already exist, you are override writting on it"
                          << ", fctId : " << static_cast<int32_t>(fctId);
            return -1;
        }
        try {
            database[lsgId][fctId] = data;
        } catch (std::exception& err) {
            LOG_DEBUG << "failed to allocate data base for lsgId/fctId : "
                          << static_cast<int32_t>(lsgId) << "/"
                          << static_cast<int32_t>(fctId);
            return -1;
        }
        return 0;
    }

    template<typename T>
    int32_t write(const lsgId_t lsgId, const fctId_t fctId, DataType<T> data)
    {
        auto it_lsg = database.find(lsgId);
        if (it_lsg == database.end()) {
            LOG_DEBUG << "lsgId not found to write"
                          << ", lsgId : " << static_cast<int32_t>(lsgId);
            return -1;
        }
        auto it_fct = it_lsg->second.find(fctId);
        if (it_fct == it_lsg->second.end()) {
            LOG_DEBUG << "fctId not found to write"
                      << ", fctId : " << static_cast<int32_t>(fctId);
            return -1;
        }

        try {
            database[lsgId][fctId] = data;
        } catch (std::exception& err) {
            LOG_DEBUG << "failed to write data base for lsgId/fctId : "
                          << static_cast<int32_t>(lsgId) << "/"
                          << static_cast<int32_t>(fctId);
            return -1;
        }
        return 0;
    }

    template<typename T>
    DataType<T> query(const lsgId_t lsgId, const fctId_t fctId)
    {
        // prevent transmitter and receiver access the same time
        std::lock_guard<std::mutex> locker(mt_loader);
        auto it_lsg = database.find(lsgId);
        if (it_lsg == database.end()) {
            LOG_DEBUG << "lsgId not found"
                          << ", lsgId : " << static_cast<int32_t>(lsgId);
            return {};
        }
        auto it_fct = it_lsg->second.find(fctId);
        if (it_fct == it_lsg->second.end()) {
            LOG_DEBUG << "fctId not found"
                          << ", fctId : " << static_cast<int32_t>(fctId);
            return {};
        }
        try {
            auto ret = std::any_cast<DataType<T>>(it_fct->second);
            return ret;
        } catch (std::exception& err) {
            LOG_DEBUG << "Failed to load database, err : "
                          << err.what();
        }
        return {};
    }
};

#endif // __FSG_DATA_BASE_HPP__
