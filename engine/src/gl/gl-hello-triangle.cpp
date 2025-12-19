#pragma once

#include "gl.hpp"

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
    }

    IFB_ENG_INTERNAL void
    gl_hello_triangle_destroy(
        gl_hello_triangle& hello_triangle) {

        gl_program_destroy(hello_triangle.program);
    }
};