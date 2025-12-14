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

    using  shader_id          = u32;
    using  shader_stage_type  = u32;
    using  shader_stage_flags = u32;
    struct shader;
    struct shader_stage;
    struct shader_program;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL bool shader_create                (shader* shdr);
    IFB_ENG_INTERNAL bool shader_add_stage_from_file   (shader* shdr, const shader_stage_type type, const cchar* file_path);
    IFB_ENG_INTERNAL bool shader_add_stage_from_source (shader* shdr, const shader_stage_type type, const cchar* src_buffer);
    IFB_ENG_INTERNAL bool shader_compile_and_link      (shader* shdr);
    IFB_ENG_INTERNAL bool shader_destroy               (shader* shdr);

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum shader_stage_type_e {
        shader_stage_type_e_vertex   = 0,
        shader_stage_type_e_fragment = 1,
        shader_stage_type_e_count    = 2
    };

    enum shader_stage_flag_e {
        shader_stage_flag_e_none     = 0,
        shader_stage_flag_e_vertex   = bit_value(shader_stage_type_e_vertex),
        shader_stage_flag_e_fragment = bit_value(shader_stage_type_e_fragment),
    };

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct shader_stage {
        gl_shader_stage gl_stage;
        gl_error        gl_error;
    };

    struct shader_program {
        gl_shader_program gl_program;
        gl_error          gl_error;
    };

    struct shader {
        shader_program program;
        struct {
            shader_stage_flags flags;
            union {
                struct {
                    shader_stage vertex;
                    shader_stage fragment;
                };             
                shader_stage array[shader_stage_type_e_count];
            };
        } stage;
    };
};

#endif //IFB_ENGINE_GRAPHICS_SHADER_HPP