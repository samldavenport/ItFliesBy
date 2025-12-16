#ifndef IFB_ENGINE_GRAPHICS_SHADER_HPP
#define IFB_ENGINE_GRAPHICS_SHADER_HPP

#include "ifb-engine.hpp"
#include <sld.hpp>
#include <sld-gl.hpp>
#include <sld-stack.hpp>

using namespace sld;

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using  shader_id          = u32;
    using  shader_stage_type  = u32;
    using  shader_stage_flags = flags;
    struct shader;
    struct shader_stage;
    struct shader_program;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL bool shader_create                       (shader* shdr, const shader_stage_flags stage_flags);
    IFB_ENG_INTERNAL bool shader_add_stage_source_from_file   (shader* shdr, const shader_stage_type  type, const cchar* file_path);
    IFB_ENG_INTERNAL bool shader_add_stage_source_from_buffer (shader* shdr, const shader_stage_type  type, const cchar* src_buffer);
    IFB_ENG_INTERNAL bool shader_link_stages                  (shader* shdr);
    IFB_ENG_INTERNAL void shader_reset                        (shader* shdr);
    IFB_ENG_INTERNAL bool shader_destroy                      (shader* shdr);

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum shader_type_ {
        shader_type_vertex                  = 0,
        shader_type_tessellation_control    = 1,
        shader_type_tessellation_evaluation = 2,
        shader_type_geometry                = 3,
        shader_type_fragment                = 4,
        shader_type_compute                 = 5,
        shader_type_count                   = 6
    };

    enum pipeline_stage_flag_ {
        pipeline_stage_flag_none                    = 0,
        pipeline_stage_flag_vertex                  = bit_value(shader_type_vertex),
        pipeline_stage_flag_tessellation_control    = bit_value(shader_type_tessellation_control),
        pipeline_stage_flag_tessellation_evaluation = bit_value(shader_type_tessellation_evaluation),
        pipeline_stage_flag_geometry                = bit_value(shader_type_geometry),    
        pipeline_stage_flag_fragment                = bit_value(shader_type_fragment),
        pipeline_stage_flag_compute                 = bit_value(shader_type_compute)
    };

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct shader_stage {
        gl_shader gl_stage;
        gl_error        gl_error;
    };

    struct shader_program {
        gl_program gl_program;
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
                shader_stage array[shader_type_e_count];
            };
        } stage;
    };
};

#endif //IFB_ENGINE_GRAPHICS_SHADER_HPP