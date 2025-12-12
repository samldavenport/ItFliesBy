#ifndef IFB_ENGINE_SHADER_HPP
#define IFB_ENGINE_SHADER_HPP

#include "ifb-engine.hpp"
#include <sld-stack.hpp>
#include <sld-gl.hpp>

using namespace sld;

namespace ifb::eng {

    struct shader {
        gl_shader id;
        struct {
            gl_shader_stage vertex;
            gl_shader_stage fragment;
        } stage;
    };


};

#endif //IFB_ENGINE_SHADER_HPP