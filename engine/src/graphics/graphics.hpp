#ifndef IFB_ENGINE_GRAPHICS_HPP
#define IFB_ENGINE_GRAPHICS_HPP

#include "ifb-engine.hpp"
#include <sld.hpp>
#include <sld-gl.hpp>
#include <sld-stack.hpp>

using namespace sld;

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using  graphics_shader_type = u32;
    struct graphics_pipeline_flags;
    struct graphics_pipeline;
    struct graphics_shader;
    struct graphics_program;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    // pipeline
    IFB_ENG_INTERNAL void graphics_pipeline_init                                   (graphics_pipeline& pipeline);
    IFB_ENG_INTERNAL bool graphics_pipeline_cleanup                                (graphics_pipeline& pipeline);
    IFB_ENG_INTERNAL void graphics_pipeline_clear_errors                           (graphics_pipeline& pipeline);
    IFB_ENG_INTERNAL bool graphics_pipeline_compile_shader_vertex                  (graphics_pipeline& pipeline, const cchar* shader_src);
    IFB_ENG_INTERNAL bool graphics_pipeline_compile_shader_tessellation_control    (graphics_pipeline& pipeline, const cchar* shader_src);
    IFB_ENG_INTERNAL bool graphics_pipeline_compile_shader_tessellation_evaluation (graphics_pipeline& pipeline, const cchar* shader_src);
    IFB_ENG_INTERNAL bool graphics_pipeline_compile_shader_geometry                (graphics_pipeline& pipeline, const cchar* shader_src);
    IFB_ENG_INTERNAL bool graphics_pipeline_compile_shader_fragment                (graphics_pipeline& pipeline, const cchar* shader_src);

    // program
    IFB_ENG_INTERNAL bool graphics_program_create        (graphics_program& program);
    IFB_ENG_INTERNAL bool graphics_program_destroy       (graphics_program& program);
    IFB_ENG_INTERNAL bool graphics_program_link_pipeline (graphics_program& program, graphics_pipeline& pipeline);

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum graphics_shader_type_ {
        graphics_shader_type_vertex                  = 0,
        graphics_shader_type_tessellation_control    = 1,
        graphics_shader_type_tessellation_evaluation = 2,
        graphics_shader_type_geometry                = 3,
        graphics_shader_type_fragment                = 4,
        graphics_shader_type_count                   = 5
    };

    enum graphics_pipeline_flag_ {
        graphics_pipeline_flag_none                    = 0,
        graphics_pipeline_flag_vertex                  = bit_value(graphics_shader_type_vertex),
        graphics_pipeline_flag_tessellation_control    = bit_value(graphics_shader_type_tessellation_control),
        graphics_pipeline_flag_tessellation_evaluation = bit_value(graphics_shader_type_tessellation_evaluation),
        graphics_pipeline_flag_geometry                = bit_value(graphics_shader_type_geometry),    
        graphics_pipeline_flag_fragment                = bit_value(graphics_shader_type_fragment)
    };

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct graphics_pipeline_flags : sld::flags {
    };

    struct graphics_shader {
        gl_shader gl_shader;
        gl_error  gl_error;
    };

    struct graphics_program {
        gl_program              gl_program;
        gl_error                gl_error;
        graphics_pipeline_flags pipeline_flags;
    };

    struct graphics_pipeline {
        union {
            struct {
                graphics_shader vertex;
                graphics_shader tessellation_control;
                graphics_shader tessellation_evaluation;
                graphics_shader geometry;
                graphics_shader fragment;
            };
            graphics_shader array[graphics_shader_type_count];
        } shader;
    };
};

#endif //IFB_ENGINE_GRAPHICS_HPP