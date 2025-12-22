#pragma once

#include "gl.hpp"

namespace ifb::eng {

    static gl_state _state;

    IFB_ENG_INTERNAL void
    gl_context_init(
        void) {

        const bool did_init = (glewInit() == GLEW_OK);
        assert(did_init);

        _state.error                   = GL_ERROR_SUCCESS;
        _state.object_id.program       = GL_ID_INVALID;
        _state.object_id.vertex        = GL_ID_INVALID;
        _state.object_id.vertex_buffer = GL_ID_INVALID;
        _state.object_id.index_buffer  = GL_ID_INVALID;

        // for good measure, ensure GL state is clear
        glBindVertexArray (0);
        glBindBuffer      (GL_ARRAY_BUFFER,         0);
        glBindBuffer      (GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    IFB_ENG_INTERNAL const gl_state&
    gl_context_get_state(
        void) {

        return(_state);
    }

    IFB_ENG_INTERNAL void
    gl_context_clear_errors(
        void) {

        constexpr s32 MAX_ERRORS = 0x7FFFFFFF;

        _state.error = GL_ERROR_SUCCESS; 
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

	    glEnable(GL_MULTISAMPLE);
        _state.error = glGetError();
        assert(_state.error == GL_ERROR_SUCCESS);

	    glEnable(GL_BLEND);
        _state.error = glGetError();
        assert(_state.error == GL_ERROR_SUCCESS);

	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);        
        _state.error = glGetError();
        assert(_state.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void
    gl_context_enable_depth_rendering(
        void) {

	    glEnable(GL_DEPTH_TEST);
        _state.error = glGetError();
        assert(_state.error == GL_ERROR_SUCCESS);

	    glDepthFunc (GL_LESS);
        _state.error = glGetError();
        assert(_state.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void
    gl_context_set_program(
        gl_program& program) {

        assert(program.is_valid());

        gl_context_clear_errors();

        glUseProgram(program.id);
        _state.error             = glGetError();
        _state.object_id.program = program.id;

        assert(_state.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void
    gl_context_set_vertex_buffer(
        gl_buffer& buffer) {

        assert(buffer.is_valid());

        gl_context_clear_errors();

        glBindBuffer(GL_ARRAY_BUFFER, buffer.id);
        _state.error                   = glGetError();
        _state.object_id.vertex_buffer = buffer.id;
        assert(_state.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void
    gl_context_set_index_buffer(
        gl_buffer& buffer) {

        assert(buffer.is_valid());

        gl_context_clear_errors();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.id);
        _state.error                  = glGetError();
        _state.object_id.index_buffer = buffer.id;
        assert(_state.error == GL_ERROR_SUCCESS);
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
        _state.error              = glGetError(); 
        _state.buffer.data.vertex = buffer_data;
        _state.buffer.size.vertex = buffer_size;
        assert(_state.error == GL_ERROR_SUCCESS);        
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
        _state.error              = glGetError(); 
        _state.buffer.data.index  = buffer_data;
        _state.buffer.size.index  = buffer_size;
        assert(_state.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void
    gl_context_set_vertex(
        gl_vertex& vertex) {
        
        assert(vertex.is_valid());

        gl_context_clear_errors();
        glBindVertexArray(vertex.id);
        _state.error            = glGetError();
        _state.object_id.vertex = vertex.id;
        assert(_state.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void
    gl_context_render(
        void) {

        gl_context_clear_errors();

        // ensure properties are set
        bool can_render = true;
        can_render &= (_state.error                   == GL_ERROR_SUCCESS);
        can_render &= (_state.object_id.program       != GL_ID_INVALID);
        can_render &= (_state.object_id.vertex        != GL_ID_INVALID);
        can_render &= (_state.object_id.vertex_buffer != GL_ID_INVALID);
        can_render &= (_state.object_id.index_buffer  != GL_ID_INVALID);
        can_render &= (_state.buffer.data.vertex      != NULL);
        can_render &= (_state.buffer.data.index       != NULL);
        can_render &= (_state.buffer.size.vertex      != 0);
        can_render &= (_state.buffer.size.index       != 0);
        assert(can_render);

        // draw the indexed vertices
        constexpr GLenum draw_mode = GL_TRIANGLES;
        constexpr GLenum draw_type = GL_UNSIGNED_INT; 
        constexpr void*  draw_data = NULL; // we draw whatever index buffer is bound
        glDrawElements(
            draw_mode,
            _state.buffer.size.index,
            draw_type,
            draw_data
        );
        _state.error = glGetError();
        assert(_state.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void 
    gl_context_reset(
        void) {

        _state.error = GL_ERROR_SUCCESS;
        glBindVertexArray (0);
        glBindBuffer      (GL_ARRAY_BUFFER,         0);
        glBindBuffer      (GL_ELEMENT_ARRAY_BUFFER, 0);
        gl_context_clear_errors();
    }
};