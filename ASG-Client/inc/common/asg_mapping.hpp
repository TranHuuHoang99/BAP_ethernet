#ifndef __ASG_MAPPING_HPP__
#define __ASG_MAPPING_HPP__

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

extern "C" {
#include "bap_defines.h"
} // extern "C"

struct ClimateZoneBridge {
    ClimateZoneBridge(void) = default;
    ~ClimateZoneBridge(void) = default;
    std::map<lsgId_t, std::map<fctId_t, std::map<std::type_index, std::any>>> callback_map;

    template<typename Signature, typename F>
    void registerCb(const lsgId_t lsgId, const fctId_t fctId, F&& cb)
    {
        // auto it_fct = callback_map[lsgId].find(fctId);
        // if (it_fct != callback_map[lsgId].end()) {
        //     std::cout << "Warning !!! : you are override writting on existed fctId : "
        //               << static_cast<int32_t>(fctId) << '\n';
        // }
        try {
            const std::type_index typekey = typeid(std::function<Signature>);
            callback_map[lsgId][fctId][typekey] = std::function<Signature>(std::forward<F>(cb));
            std::cout << "[CLIENT] Register callback for lsgId/fctId : "
                      << static_cast<int32_t>(lsgId) << '/' << static_cast<int32_t>(fctId) << '\n';
        } catch (std::exception& err) {
            std::cerr << "[CLIENT] Warning !!! : can not assign callback function, err : "
                      << err.what() << '\n';
        }
    }

    template<typename R, typename... Args>
    R executeCb(const lsgId_t lsgId, const fctId_t fctId, Args&&... args)
    {
        auto it_lsg = callback_map.find(lsgId);
        if (it_lsg == callback_map.end()) {
            std::cout << "Error !!! : Can not find such lsgId : "
                      << static_cast<int32_t>(lsgId) << '\n';
            return R();
        }
        auto it_fct = it_lsg->second.find(fctId);
        if (it_fct == it_lsg->second.end()) {
            std::cout << "Error !!! : Can not find such fctId : "
                      << static_cast<int32_t>(fctId) << '\n';
            return R();
        }

        using TargetFuncType = std::function<R(lsgId_t, fctId_t, std::decay_t<Args>...)>;
        std::type_index typekey = typeid(TargetFuncType);

        auto& inner_map = it_fct->second;
        auto it_func = inner_map.find(typekey);
        if (it_func == inner_map.end()) {
            std::cout << "Error !!! : can not find such signature\n";
            return R();
        }

        try {
            auto func = std::any_cast<std::function<R(lsgId_t,
                                                      fctId_t,
                                                      std::decay_t<Args>...)>>(it_func->second);
            return func(lsgId, fctId, std::forward<Args>(args)...);
        } catch (const std::exception& e) {
            std::cout << "Error !!! : Arguments mismatch for this callback: " << e.what() << '\n';
            return R();
        }
        return R();
    }
};

template<typename T>
struct ClimateDataType {
    T data;
    uint32_t len;
};

struct ClimateLoadBalancer {
    std::mutex mt_loader;
    ClimateLoadBalancer(void)
    {
        try {
            tx = std::make_shared<ClimateZoneBridge>();
            rx = std::make_shared<ClimateZoneBridge>();
        } catch (std::bad_alloc& err) {
            std::cerr << "[STORAGE] Storage failed to allocate callback mapping for tx/rx\n";
        }
    }
    ~ClimateLoadBalancer(void) = default;
    std::shared_ptr<ClimateZoneBridge> tx;
    std::shared_ptr<ClimateZoneBridge> rx;
    std::map<lsgId_t, std::map<fctId_t, std::any>> database;

    template<typename T>
    void insert(const lsgId_t lsgId, const fctId_t fctId, ClimateDataType<T> data)
    {
        auto it_lsg = database.find(lsgId);
        if (it_lsg != database.end()) {
            std::cout << "[STORAGE] lsgId already exist, you are override writting on it"
                      << ", lsgId : " << static_cast<int32_t>(lsgId) << '\n';
        }
        auto it_fct = it_lsg->second.find(fctId);
        if (it_fct != it_lsg->second.end()) {
            std::cout << "[STORAGE] fctId already exist, you are override writting on it"
                      << ", fctId : " << static_cast<int32_t>(fctId) << '\n';
        }
        try {
            database[lsgId][fctId] = data;
        } catch (std::exception& err) {
            std::cout << "[STORAGE] failed to allocate data base for lsgId/fctId : "
                      << static_cast<int32_t>(lsgId) << "/"
                      << static_cast<int32_t>(fctId) << '\n';
        }
    }

    template<typename T>
    ClimateDataType<T> query(const lsgId_t lsgId, const fctId_t fctId)
    {
        // prevent transmitter and receiver access the same time
        std::lock_guard<std::mutex> locker(mt_loader);
        auto it_lsg = database.find(lsgId);
        if (it_lsg == database.end()) {
            std::cout << "[STORAGE] lsgId not found"
                      << ", lsgId : " << static_cast<int32_t>(lsgId) << '\n';
            return {};
        }
        auto it_fct = it_lsg->second.find(fctId);
        if (it_fct == it_lsg->second.end()) {
            std::cout << "[STORAGE] fctId not found"
                      << ", fctId : " << static_cast<int32_t>(fctId) << '\n';
            return {};
        }
        try {
            auto ret = std::any_cast<ClimateDataType<T>>(it_fct->second);
            return ret;
        } catch (std::exception& err) {
            std::cout << "[STORAGE] Failed to load database, err : "
                      << err.what() << '\n';
        }
        return {};
    }
};

#endif // __ASG_MAPPING_HPP__
