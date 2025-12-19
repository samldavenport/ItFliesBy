#ifndef GL_HPP
#define GL_HPP

#include "ifb-engine.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using gl_error         = GLenum; 
    using gl_status        = GLint; 
    using gl_id            = GLuint;
    using gl_vertex        = GLuint; 
    using gl_buffer        = GLuint;
    using gl_buffer_type   = GLenum;
    using gl_buffer_useage = GLenum;

    struct gl_pipeline;
    struct gl_program;
    struct gl_shader;
    struct gl_hello_triangle;

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr gl_error GL_ERROR_SUCCESS = 0;
    constexpr gl_id    GL_ID_INVALID    = 0;

    constexpr cchar GL_HELLO_TRIANGLE_SHADER_VERTEX[] = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    constexpr cchar GL_HELLO_TRIANGLE_SHADER_FRAGMENT[] =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    // context
    IFB_ENG_INTERNAL void gl_context_init                   (void);
    IFB_ENG_INTERNAL void gl_context_clear_errors           (void);
    IFB_ENG_INTERNAL void gl_context_enable_smoothing       (void);
    IFB_ENG_INTERNAL void gl_context_enable_depth_rendering (void);

    // pipeline
    IFB_ENG_INTERNAL void gl_pipeline_init                                   (gl_pipeline& pipeline);
    IFB_ENG_INTERNAL void gl_pipeline_cleanup                                (gl_pipeline& pipeline);
    IFB_ENG_INTERNAL bool gl_pipeline_compile_shader_vertex                  (gl_pipeline& pipeline, const cchar* shader_src);
    IFB_ENG_INTERNAL bool gl_pipeline_compile_shader_tessellation_control    (gl_pipeline& pipeline, const cchar* shader_src);
    IFB_ENG_INTERNAL bool gl_pipeline_compile_shader_tessellation_evaluation (gl_pipeline& pipeline, const cchar* shader_src);
    IFB_ENG_INTERNAL bool gl_pipeline_compile_shader_geometry                (gl_pipeline& pipeline, const cchar* shader_src);
    IFB_ENG_INTERNAL bool gl_pipeline_compile_shader_fragment                (gl_pipeline& pipeline, const cchar* shader_src);

    // program
    IFB_ENG_INTERNAL void gl_program_create        (gl_program& program);
    IFB_ENG_INTERNAL void gl_program_destroy       (gl_program& program);
    IFB_ENG_INTERNAL bool gl_program_link_pipeline (gl_program& program, gl_pipeline& pipeline);

    // hello triangle
    IFB_ENG_INTERNAL void gl_hello_triangle_create  (gl_hello_triangle& hello_triangle);
    IFB_ENG_INTERNAL void gl_hello_triangle_destroy (gl_hello_triangle& hello_triangle);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct gl_program {
        gl_id    id;
        gl_error error;
    };

    struct gl_shader {
        gl_id    id;
        gl_error error;
    };

    struct gl_pipeline {
        gl_shader vertex;
        gl_shader tessellation_control;
        gl_shader tessellation_evaluation;
        gl_shader geometry;
        gl_shader fragment;
    };

    struct gl_hello_triangle {
        gl_program  program;
        gl_pipeline pipeline;        
    };
};

#endif //GL_HPP