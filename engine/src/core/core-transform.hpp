#ifndef CORE_TRANSFORM_HPP
#define CORE_TRANSFORM_HPP

#include "ifb-engine.hpp"
#include "core-id.hpp"
#include "math.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using transform_id = id;
    
    struct transform;
    struct translation;
    struct scale;
    struct rotation;

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct translation  : vec3 { };
    struct scale        : vec3 { };
    struct rotation     : vec3 { };

    struct transform {
        transform_id id;
        translation  translation;
        scale        scale;
        rotation     rotation;        
    };
};

#endif //CORE_TRANSFORM_HPP