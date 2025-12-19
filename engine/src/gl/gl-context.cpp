#pragma once

#include "gl.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    gl_context_init(
        void) {

        const bool did_init = (glewInit() == GLEW_OK);
        assert(did_init);
    }

    IFB_ENG_INTERNAL void
    gl_context_clear_errors(
        void) {

        constexpr s32 MAX_ERRORS = 0x7FFFFFFF;

        for (
            u32 index = 0;
            index < MAX_ERRORS;
            ++index) {

            if (glGetError() == GL_ERROR_SUCCESS) {
                break;
            }
        }
    }

    IFB_ENG_INTERNAL void
    gl_context_enable_smoothing(
        void) {

        bool did_enable = true;

	    glEnable(GL_MULTISAMPLE);
        did_enable &= (glGetError() == GL_ERROR_SUCCESS);

	    glEnable(GL_BLEND);
        did_enable &= (glGetError() == GL_ERROR_SUCCESS);

	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);        
        did_enable &= (glGetError() == GL_ERROR_SUCCESS);

        assert(did_enable);
    }

    IFB_ENG_INTERNAL void
    gl_context_enable_depth_rendering(
        void) {

        bool did_enable = true;

	    glEnable(GL_DEPTH_TEST);
        did_enable &= (glGetError() == GL_ERROR_SUCCESS);

	    glDepthFunc (GL_LESS);
        did_enable &= (glGetError() == GL_ERROR_SUCCESS);

        assert(did_enable);
    }

    IFB_ENG_INTERNAL void
    gl_context_set_program(
        gl_program& program) {

        assert(program.is_valid());

        gl_context_clear_errors();

        glUseProgram(program.id);
        assert(glGetError() == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void
    gl_context_set_vertex_buffer(
        gl_buffer& buffer) {

        assert(buffer.is_valid());

        gl_context_clear_errors();
        glBindBuffer(GL_ARRAY_BUFFER, buffer.id);
        assert(glGetError() == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void
    gl_context_set_index_buffer(
        gl_buffer& buffer) {

        assert(buffer.is_valid());

        gl_context_clear_errors();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.id);
        assert(glGetError() == GL_ERROR_SUCCESS);        
    }

    IFB_ENG_INTERNAL void
    gl_context_set_vertex_buffer_data(
        const byte* buffer_data,
        const u32   buffer_size) {

        assert(
            buffer_data != NULL &&
            buffer_size != 0
        );

        gl_context_clear_errors();
        glBufferData(GL_ARRAY_BUFFER, buffer_size, buffer_data, GL_STATIC_DRAW);
        assert(glGetError() == GL_ERROR_SUCCESS);        
    }
    
    IFB_ENG_INTERNAL void
    gl_context_set_index_buffer_data(
        const u32* buffer_data,
        const u32  buffer_size) {

        assert(
            buffer_data != NULL &&
            buffer_size != 0
        );

        gl_context_clear_errors();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_size, buffer_data, GL_STATIC_DRAW);
        assert(glGetError() == GL_ERROR_SUCCESS);        
    }

};