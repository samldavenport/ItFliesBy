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
    struct shader_stage;
    struct shader_manager;
    struct shader_program;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    shader_create  ();
    shader_destroy ();
    

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

    struct shader_stage {
        gl_shader_stage gl_stage;
        gl_error        gl_error;
    };

    struct shader {
        gl_shader_program gl_program;
        gl_error          gl_error;
    };

    enum shader_id_e : u32 {
        shader_id_e_solid_quad = 0,
        shader_id_e_textured_quad = 0
    };



};

#endif //IFB_ENGINE_GRAPHICS_SHADER_HPP