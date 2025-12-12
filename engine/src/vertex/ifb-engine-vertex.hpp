#ifndef IFB_ENGINE_VERTEX_HPP
#define IFB_ENGINE_VERTEX_HPP

#include "ifb-engine.hpp"

namespace ifb::eng {

    using vertex_attribute_type  = u32;  
    using vertex_attribute_flags = u32;

    enum vertex_attribute_type_e {
        vertex_attribute_type_e_position_2d    = 0,
        vertex_attribute_type_e_position_3d    = 1,
        vertex_attribute_type_e_texture_coord  = 2,
        vertex_attribute_type_e_normal         = 3,        
        vertex_attribute_type_e_color_rgba_32  = 4,        
        vertex_attribute_type_e_color_rgba_128 = 5,        
        vertex_attribute_type_e_count          = 6        
    };

    enum vertex_attribute_flag_e {
        vertex_attribute_flag_e_none           = 0
        vertex_attribute_type_e_position_3d    = 1,
        vertex_attribute_type_e_texture_coord  = 2,
        vertex_attribute_type_e_normal         = 3,
        vertex_attribute_type_e_color_rgba_32  = 4,
        vertex_attribute_type_e_color_rgba_128 = 4,
    };

    const u32
    vertex_attribute_size(
        const vertex_attribute_type& type) {

        assert(type <= vertex_attribute_flag_e_count);

        constexpr u32 size_array[vertex_attribute_type_e_count] = {
            sizeof(f32) * 2,  // vertex_attribute_type_e_position_2d
            sizeof(f32) * 3,  // vertex_attribute_type_e_position_3d
            sizeof(u32) * 2,  // vertex_attribute_type_e_texture_coord
            sizeof(f32) * 3,  // vertex_attribute_type_e_normal
            sizeof(u32),      // vertex_attribute_type_e_color_rgba_32
            sizeof(f32) * 4   // vertex_attribute_type_e_color_rgba_32
        };

        const u32 size = size_array[type];
        return(size);
    };
};

#endif //IFB_ENGINE_VERTEX_HPP