#ifndef IFB_ENGINE_GRAPHICS_SHADER_HPP
#define IFB_ENGINE_GRAPHICS_SHADER_HPP

#include "ifb-engine.hpp"
#include <sld-stack.hpp>
#include <sld-gl.hpp>

using namespace sld;


namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using  shader_id = u32;

    struct shader;
    struct shader_stages;
    struct shader_manager;

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct shader_manager {
        u32 count;
        struct {
            shader*        shader;
            shader_stages* stages;
        } array;
    };

    struct shader_stages {
        gl_shader_stage vertex;
        gl_shader_stage fragment;
    };

    struct shader {
        gl_shader_program program;
    };

    enum shader_id_e : u32 {
        shader_id_e_solid_quad = 0,
        shader_id_e_textured_quad = 0
    };

};

#endif //IFB_ENGINE_GRAPHICS_SHADER_HPP