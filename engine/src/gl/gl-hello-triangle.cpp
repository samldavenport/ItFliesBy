#pragma once

#include "gl.hpp"
#include "sld-vector.hpp"
namespace ifb::eng {

    IFB_ENG_INTERNAL void
    gl_hello_triangle_create(
        gl_hello_triangle& hello_triangle) {

        // compile the pipeline
        bool did_compile = true;
        gl_pipeline_init(hello_triangle.pipeline);
        did_compile &= gl_pipeline_compile_shader_vertex   (hello_triangle.pipeline, GL_HELLO_TRIANGLE_SHADER_VERTEX);
        did_compile &= gl_pipeline_compile_shader_fragment (hello_triangle.pipeline, GL_HELLO_TRIANGLE_SHADER_FRAGMENT);

        // create the program and link the pipeline
        gl_program_create(hello_triangle.program);
        const bool did_link = gl_program_link_pipeline(
            hello_triangle.program,
            hello_triangle.pipeline);
        assert(did_link);

        // clean up the pipeline
        gl_pipeline_cleanup(hello_triangle.pipeline);

        // create the buffers and vertex
        gl_buffer_create (hello_triangle.buffer.vertex);
        gl_buffer_create (hello_triangle.buffer.index);
        gl_vertex_create (hello_triangle.vertex);

        // define vertex attributes
        constexpr u32 position_index  = 0;
        constexpr u32 position_offset = 0;
        constexpr u32 vertex_size     = sizeof(vec2); 
        gl_context_set_vertex_buffer (hello_triangle.buffer.vertex);
        gl_context_set_vertex        (hello_triangle.vertex);
        gl_vertex_attribute_set_vec3 (hello_triangle.vertex, vertex_size, position_index, position_offset);
        gl_vertex_attribute_enable   (hello_triangle.vertex, position_index);

    }

    IFB_ENG_INTERNAL void
    gl_hello_triangle_destroy(
        gl_hello_triangle& hello_triangle) {

        gl_program_destroy(hello_triangle.program);
    }

    IFB_ENG_INTERNAL void
    gl_hello_triangle_render(
        gl_hello_triangle& hello_triangle) {

        const byte* data_buffer_vertex = (byte*)GL_HELLO_TRIANGLE_VERTICES;
        const u32*  data_buffer_index  = (u32*)GL_HELLO_TRIANGLE_INDICES;
        const u32   size_buffer_vertex = sizeof(GL_HELLO_TRIANGLE_VERTICES);
        const u32   size_buffer_index  = sizeof(GL_HELLO_TRIANGLE_INDICES);

        gl_context_set_program            (hello_triangle.program);
        gl_context_set_vertex_buffer      (hello_triangle.buffer.vertex);
        gl_context_set_index_buffer       (hello_triangle.buffer.index);
        gl_context_set_vertex_buffer_data (data_buffer_vertex, size_buffer_vertex);
        gl_context_set_index_buffer_data  (data_buffer_index,  size_buffer_index);
    }

};