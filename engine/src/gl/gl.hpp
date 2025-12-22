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
    using gl_buffer_type   = GLenum;
    using gl_buffer_useage = GLenum;

    struct gl_object;
    struct gl_pipeline;
    struct gl_program;
    struct gl_shader;
    struct gl_buffer;
    struct gl_vertex;
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
    constexpr f32 GL_HELLO_TRIANGLE_VERTICES[] = {
         0.5f,  0.5f, 0.0f, // top right
         0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f  // top left 
    };
    constexpr u32 GL_HELLO_TRIANGLE_INDICES[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    // context
    IFB_ENG_INTERNAL void gl_context_init                   (void);
    IFB_ENG_INTERNAL void gl_context_clear_errors           (void);
    IFB_ENG_INTERNAL void gl_context_enable_smoothing       (void);
    IFB_ENG_INTERNAL void gl_context_enable_depth_rendering (void);
    IFB_ENG_INTERNAL void gl_context_set_program            (gl_program& program);
    IFB_ENG_INTERNAL void gl_context_set_vertex_buffer      (gl_buffer& buffer);
    IFB_ENG_INTERNAL void gl_context_set_vertex_buffer_data (const byte* buffer_data, const u32 buffer_size);
    IFB_ENG_INTERNAL void gl_context_set_index_buffer       (gl_buffer&  buffer);
    IFB_ENG_INTERNAL void gl_context_set_index_buffer_data  (const u32*  buffer_data, const u32 buffer_size);
    IFB_ENG_INTERNAL void gl_context_set_vertex             (gl_vertex& vertex);

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

    // buffer
    IFB_ENG_INTERNAL void gl_buffer_create  (gl_buffer& buffer);
    IFB_ENG_INTERNAL void gl_buffer_destroy (gl_buffer& buffer);

    // vertex
    IFB_ENG_INTERNAL void gl_vertex_create            (gl_vertex& vertex);
    IFB_ENG_INTERNAL void gl_vertex_destroy           (gl_vertex& vertex);
    IFB_ENG_INTERNAL bool gl_vertex_attribute_enable  (gl_vertex& vertex, const u32 index);
    IFB_ENG_INTERNAL bool gl_vertex_attribute_disable (gl_vertex& vertex, const u32 index);
    IFB_ENG_INTERNAL bool gl_vertex_attribute_set_u32 (gl_vertex& vertex, const u32 vertex_size, const u32 attribute_index, const u32 attribute_offset);
    IFB_ENG_INTERNAL bool gl_vertex_attribute_set_f32 (gl_vertex& vertex, const u32 vertex_size, const u32 attribute_index, const u32 attribute_offset);

    // hello triangle
    IFB_ENG_INTERNAL void gl_hello_triangle_create  (gl_hello_triangle& hello_triangle);
    IFB_ENG_INTERNAL void gl_hello_triangle_destroy (gl_hello_triangle& hello_triangle);
    IFB_ENG_INTERNAL void gl_hello_triangle_render  (gl_hello_triangle& hello_triangle);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct gl_object {
        gl_id    id;
        gl_error error;

        inline void
        reset(void) {
            this->id    = GL_ID_INVALID;
            this->error = GL_ERROR_SUCCESS;
        }

        inline bool
        is_valid(void) {
            return(
                this->id    != GL_ID_INVALID    &&
                this->error == GL_ERROR_SUCCESS
            );
        }

        inline void
        clear_error(void) {
            this->error = GL_ERROR_SUCCESS;
        }
    };

    struct gl_program : gl_object { };
    struct gl_shader  : gl_object { };
    struct gl_buffer  : gl_object { };
    struct gl_vertex  : gl_object { };


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
        struct {
            gl_buffer vertex;
            gl_buffer index;
        } buffer;
    };
};

#endif //GL_HPP