#ifndef CORE_HASH_HPP
#define CORE_HASH_HPP

#include "ifb-engine.hpp"
#include <zlib-ng.h>

namespace ifb::eng {

    inline u32
    hash_string(
        const cchar* cstr,
        const u32    length) {

        assert(
            cstr   != NULL &&
            length != 0
        );

        static u32 hash = zng_crc32(0, Z_NULL, 0);

        hash = zng_crc32(hash, (byte*)cstr, length);        
        return(hash);
    }

};

#endif //CORE_HASH_HPP