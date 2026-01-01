#ifndef MANAGERS_HPP
#define MANAGERS_HPP

#include "ifb-engine.hpp"
#include "math.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    

    struct transform_manager;
    struct quad_manager;

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct transform_manager {
        u32 capacity;
        u32 count;
        struct {
            vec3* translation;
            vec3* scale;
            vec3* rotation;
        } data;
    };
};

#endif //MANAGERS_HPP