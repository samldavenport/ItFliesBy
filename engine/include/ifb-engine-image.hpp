#ifndef IFB_ENG_IMAGE_HPP
#define IFB_ENG_IMAGE_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-file.hpp"

namespace ifb::eng {

    struct img_t;
    struct img_info_t;
    struct img_buffer;

    IFB_ENG_API bool img_get_info (const file_h32_t file_h, img_info_t&   img_info);
    IFB_ENG_API bool img_load     (const file_h32_t file_h, img_buffer& img_buffer);

    struct img_buffer {
        byte* data;
        u32   size;
        u32   channels;
    };

    struct img_info_t {
        u32 pixel_width;
        u32 pixel_height;
        u32 channel_count;
        u32 mem_size;
    };
};

#endif //IFB_ENG_IMAGE_HPP
