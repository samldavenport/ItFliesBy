#ifndef IFB_ENGINE_COMPONENTS_HPP
#define IFB_ENGINE_COMPONENTS_HPP

#include "ifb-engine.hpp"
#include "math.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    // transforms
    struct transform;
    struct translation;
    struct scale;
    struct roation;

    //-------------------------------------------------------------------
    // TRANSFORMS
    //-------------------------------------------------------------------

    struct translation : vec3 { };
    struct scale       : vec3 { };
    struct rotation    : vec3 { };

    struct transform {
        translation translation;
        scale       scale;
        rotation    rotation;        
    };
};

#endif //MANAGERS_HPP