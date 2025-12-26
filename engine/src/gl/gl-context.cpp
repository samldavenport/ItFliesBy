#pragma once

#include "gl.hpp"

namespace ifb::eng {

    static gl_state _state;

    IFB_ENG_INTERNAL void
    gl_context_init(
        void) {

        _state.error                                  = GL_ERROR_SUCCESS;
        _state.object_id.program                      = GL_ID_INVALID;
        _state.object_id.vertex                       = GL_ID_INVALID;
        _state.object_id.vertex_buffer                = GL_ID_INVALID;
        _state.object_id.index_buffer                 = GL_ID_INVALID;
        _state.draw_data.indices.buffer_data.as_byte  = NULL;
        _state.draw_data.indices.buffer_size          = 0;
        _state.draw_data.vertices.buffer_data.as_byte = NULL;
        _state.draw_data.vertices.buffer_size         = 0;

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

        gl_context_clear_errors();

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

        gl_context_clear_errors();

	    glEnable(GL_DEPTH_TEST);
        _state.error = glGetError();
        assert(_state.error == GL_ERROR_SUCCESS);

	    glDepthFunc (GL_LESS);
        _state.error = glGetError();
        assert(_state.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void
    gl_context_set_viewport(
        const gl_viewport& viewport) {

        gl_context_clear_errors();

        glViewport(
            viewport.x,
            viewport.y,
            viewport.width,
            viewport.height
        );

        _state.error = glGetError();
        assert(_state.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void
    gl_context_clear_viewport(
        void) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    IFB_ENG_INTERNAL void
    gl_context_set_clear_color(
        const u32 hex_rgba) {

        gl_context_clear_errors();

        _state.clear_color.from_hex(hex_rgba);

        glClearColor(
            _state.clear_color.r,
            _state.clear_color.g,
            _state.clear_color.b,
            _state.clear_color.a
        );

        _state.error = glGetError();
        assert(_state.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void
    gl_context_set_viewport(
        const u32 x,
        const u32 y,
        const u32 width,
        const u32 height) {

        gl_context_clear_errors();

        _state.viewport.x      = x;
        _state.viewport.y      = y;
        _state.viewport.width  = width;
        _state.viewport.height = height;
        glViewport(
            _state.viewport.x,
            _state.viewport.y,
            _state.viewport.width,
            _state.viewport.height
        );

        _state.error = glGetError();
        assert(_state.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void
    gl_context_set_program(
        const gl_program& program) {

        assert(program.is_valid());

        gl_context_clear_errors();

        glUseProgram(program.id);
        _state.error             = glGetError();
        _state.object_id.program = program.id;

        assert(_state.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void
    gl_context_set_vertex_buffer(
        const gl_buffer& buffer) {

        assert(buffer.is_valid());

        gl_context_clear_errors();

        glBindBuffer(GL_ARRAY_BUFFER, buffer.id);
        _state.error                   = glGetError();
        _state.object_id.vertex_buffer = buffer.id;
        assert(_state.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void
    gl_context_set_index_buffer(
        const gl_buffer& buffer) {

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
        _state.draw_data.vertices.buffer_data.as_byte = buffer_data;
        _state.draw_data.vertices.buffer_size         = buffer_size;
        assert(_state.error == GL_ERROR_SUCCESS);        
    }
    
    IFB_ENG_INTERNAL void
    gl_context_set_index_buffer_data(
        const u32* index_array,
        const u32  index_count) {

        assert(
            index_array != NULL &&
            index_count != 0
        );

        const u32 buffer_size = sizeof(u32) * index_count;
        gl_context_clear_errors();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_size, (void*)index_array, GL_STATIC_DRAW);
        _state.error                                = glGetError(); 
        _state.draw_data.indices.buffer_data.as_u32 = index_array;
        _state.draw_data.indices.buffer_size        = buffer_size;
        assert(_state.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL void
    gl_context_set_vertex(
        const gl_vertex& vertex) {
        
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
        assert(can_render);

        // draw the indexed vertices
        constexpr GLenum draw_mode        = GL_TRIANGLES;
        constexpr GLenum draw_type        = GL_UNSIGNED_INT; 
        constexpr void*  draw_data        = NULL; // we draw whatever index buffer is bound
        const     u32    draw_index_count = _state.draw_data.indices.count_u32(); 
        glDrawElements(
            draw_mode,
            draw_index_count,
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