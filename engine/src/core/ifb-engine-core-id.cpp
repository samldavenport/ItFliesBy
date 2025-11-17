#pragma once

#include "ifb-engine-id.hpp"
#include "ifb-engine-hash.hpp"

namespace ifb {

    IFB_ENG_API void
    eng_id_generate(
        const u32   in_count,
        const u32   in_stride,
        const byte* in_data,
        eng_id_u32_t*   out_id) {

        const bool is_valid = (
            in_count  != 0    &&
            in_stride != 0    &&
            in_data   != NULL &&
            out_id    != NULL
        );
        if (!is_valid) return;

        (void)eng_hash32_batch(
            in_count,
            in_data,
            in_stride,
            out_id
        );
    }
    
    IFB_ENG_API bool
    eng_id_search(
        const u32       in_count,
        const eng_id_u32_t  in_id,
        const eng_id_u32_t* in_search,
        u32&            out_index) {

        const bool did_find = eng_hash32_search(
            in_count,
            in_id,
            in_search,
            out_index
        );

        return(did_find);
    }
};