#ifndef GL_HPP
#define GL_HPP

#include "ifb-engine.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using gl_status        = GLint; 
    using gl_program       = GLuint;
    using gl_shader        = GLuint;
    using gl_vertex        = GLuint; 
    using gl_buffer        = GLuint;
    using gl_buffer_type   = GLenum;
    using gl_buffer_useage = GLenum;

    struct gl_pipeline;

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    constexpr gl_shader GL_SHADER_INVALID = 0;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    // context
    IFB_ENG_INTERNAL void gl_context_init                   (void);
    IFB_ENG_INTERNAL void gl_context_clear_errors           (void);
    IFB_ENG_INTERNAL bool gl_context_enable_smoothing       (void);
    IFB_ENG_INTERNAL bool gl_context_enable_depth_rendering (void);

    // pipeline
    IFB_ENG_INTERNAL void gl_pipeline_init                                   (gl_pipeline& pipeline);
    IFB_ENG_INTERNAL bool gl_pipeline_cleanup                                (gl_pipeline& pipeline);
    IFB_ENG_INTERNAL bool gl_pipeline_compile_shader_vertex                  (gl_pipeline& pipeline, const cchar* shader_src);
    IFB_ENG_INTERNAL bool gl_pipeline_compile_shader_tessellation_control    (gl_pipeline& pipeline, const cchar* shader_src);
    IFB_ENG_INTERNAL bool gl_pipeline_compile_shader_tessellation_evaluation (gl_pipeline& pipeline, const cchar* shader_src);
    IFB_ENG_INTERNAL bool gl_pipeline_compile_shader_geometry                (gl_pipeline& pipeline, const cchar* shader_src);
    IFB_ENG_INTERNAL bool gl_pipeline_compile_shader_fragment                (gl_pipeline& pipeline, const cchar* shader_src);

    // program
    IFB_ENG_INTERNAL gl_program gl_program_create        (void);
    IFB_ENG_INTERNAL void       gl_program_destroy       (const gl_program program);
    IFB_ENG_INTERNAL void       gl_program_link_pipeline (const gl_program program, const gl_pipeline& pipeline);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct gl_shader_pipeline {
        gl_shader vertex;
        gl_shader tessellation_control;
        gl_shader tessellation_evaluation;
        gl_shader geometry;
        gl_shader fragment;
    };
};

#endif //GL_HPP