#include <cstdint>

#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && defined(__ORDER_BIG_ENDIAN__)
// GCC/Clang (incl. MinGW): byte order is known at compile time.
#define HOST_IS_LITTLE (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#elif defined(_WIN32)
// Windows runs only on little-endian architectures and has no <endian.h>.
#define HOST_IS_LITTLE 1
#else
#include <endian.h>
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define HOST_IS_LITTLE 1
#else
#define HOST_IS_LITTLE 0
#endif
#endif

static inline uint16_t host_to_be16(uint16_t v){
    if constexpr (HOST_IS_LITTLE) {
        v = (uint16_t)((v>>8) | (v<<8));
    }
    return v;
}
static inline uint16_t be16_to_host(uint16_t v){
    return host_to_be16(v);
}

static inline uint32_t host_to_be32(uint32_t v){
    if constexpr (HOST_IS_LITTLE) {
        v = ((v & 0x000000FFu) << 24) | ((v & 0x0000FF00u) << 8) | ((v & 0x00FF0000u) >> 8) | ((v & 0xFF000000u) >> 24);
    }
    return v;
}
static inline uint32_t be32_to_host(uint32_t v){
    return host_to_be32(v);
}

static inline uint64_t host_to_be64(uint64_t v){
    if constexpr (HOST_IS_LITTLE) {
        v = ((v & 0x00000000000000FFull) << 56) | ((v & 0x000000000000FF00ull) << 40) | ((v & 0x0000000000FF0000ull) << 24) |
            ((v & 0x00000000FF000000ull) << 8) | ((v & 0x000000FF00000000ull) >> 8) | ((v & 0x0000FF0000000000ull) >> 24) |
            ((v & 0x00FF000000000000ull) >> 40) | ((v & 0xFF00000000000000ull) >> 56);
    }
    return v;
}
static inline uint64_t be64_to_host(uint64_t v){
    return host_to_be64(v);
}