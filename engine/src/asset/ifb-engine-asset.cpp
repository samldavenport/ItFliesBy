#pragma once

#include "ifb-engine-asset.hpp"

namespace ifb {

    IFB_ENG_FUNC void
    eng_asset_generate_id(
        const u32                 in_count,
        const eng_asset_string_t* in_name,
        eng_asset_u32_id_t*       out_id) {

        static const u32 stride = sizeof(eng_asset_string_t); 
        assert(false);

        // eng_id_generate(
        //     in_count,
        //     stride,
        //     (byte*)in_name,
        //     out_id
        // );
    }

    IFB_ENG_API void
    eng_asset_name_sanitize(
        const u32           i_count,
        eng_asset_string_t* io_name) {

        static const u32 name_size              = sizeof(eng_asset_string_t);
        static const u32 ascii_lowercase_offset = 32; 

        for (
            u32 name_index = 0;
            name_index < i_count;
            ++name_index) {

            eng_asset_string_t& name          = io_name[name_index];
            bool               is_terminated = false;

            for (
                u32 char_index = 0;
                char_index < name_size;
                ++char_index) {

                const cchar c = name.chars[char_index];

                is_terminated |= (c == 0);
                if (is_terminated) {
                    name.chars[char_index] = 0;
                    continue;                    
                }

                const bool is_lower_case   = (c >= 'a' && c <= 'z');
                const bool is_upper_case   = (c >= 'A' && c <= 'Z');
                const bool is_number       = (c >= '0' && c <= '9');
                const bool is_special_char = (!is_lower_case && !is_upper_case && !is_number);

                if      (is_terminated)   name.chars[char_index] = 0;
                else if (is_upper_case)   name.chars[char_index] = (c + ascii_lowercase_offset);
                else if (is_special_char) name.chars[char_index] = '-';
            }
        }
    }
};