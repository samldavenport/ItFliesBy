#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "ifb-engine-image.hpp"
namespace ifb::eng {

    IFB_ENG_API bool
    img_get_info(
        const file_h32_t file_h,
        img_info_t&      img_info) {

        return(false);
    }

    IFB_ENG_API bool
    img_load(
        const file_h32_t file_h,
        img_buffer_t&    img_buffer) {

        return(false);
    }
};