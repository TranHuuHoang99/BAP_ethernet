#ifndef __FSG_TYPE_HPP__
#define __FSG_TYPE_HPP__

#include <iostream>
#include <cstdint>
#include <any>
#include <functional>
#include <memory>
#include <optional>
#include <mutex>
#include <typeindex>
#include <type_traits>
#include <map>
#include <vector>
#include <string>
#include <stdlib.h>
#include <thread>
#include <queue>
#include <atomic>
#include <cstring>
#include "fsg_log.hpp"

extern "C" {
#include "bap.h"
#include "bap_util.h"
#include "bap_canubs.h"
#include "palb.h"
#include "bap_defines.h"
} // extern "C"

typedef float float32_t;
typedef double float64_t;
typedef long double float128_t;

typedef enum class AIR_DISTRIBUTE : int32_t {
    UP = 1,
    BODY = 2,
    FOOTWELL = 3,
    INVALID = 0xFF
} AirDistribute_t;

#endif // __FSG_TYPE_HPP__
