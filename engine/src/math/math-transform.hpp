#ifndef MATH_TRANSFORM_HPP
#define MATH_TRANSFORM_HPP

#include "math-mat3.hpp"
#include "math-mat4.hpp"
#include "math-vec2.hpp"
#include "math-vec3.hpp"

namespace ifb::eng {

    struct position    : vec3 { };
    struct rotation    : vec3 { };
    struct translation : vec3 { };
    struct scale       : vec3 { };
    struct transform   : mat4 { };

};

#endif //MATH_TRANSFORM_HPP