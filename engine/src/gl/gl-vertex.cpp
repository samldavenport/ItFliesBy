#pragma once

#include "gl.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    gl_vertex_create(
        gl_vertex& vertex) {

        gl_context_clear_errors();

        glGenVertexArrays(1, &vertex.id);
    
        vertex.error = glGetError();

        assert(vertex.is_valid());
    }

    IFB_ENG_INTERNAL void
    gl_vertex_destroy(
        gl_vertex& vertex) {

        gl_context_clear_errors();

        glDeleteVertexArrays(1, &vertex.id);
    
        vertex.error = glGetError();
        assert(vertex.error == GL_ERROR_SUCCESS);

        vertex.id = GL_ID_INVALID;
    }

    IFB_ENG_INTERNAL bool
    gl_vertex_attribute_enable(
        gl_vertex& vertex,
        const u32  index) {

        gl_context_clear_errors();

        assert(vertex.is_valid());

        glEnableVertexAttribArray(index);

        vertex.error = glGetError();
        return(vertex.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL bool
    gl_vertex_attribute_disable(
        gl_vertex& vertex,
        const u32  index) {

        gl_context_clear_errors();

        assert(vertex.is_valid());

        glDisableVertexAttribArray(index);

        vertex.error = glGetError();
        return(vertex.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL bool
    gl_vertex_attribute_set_u32(
        gl_vertex& vertex,
        const u32  vertex_size,
        const u32  attribute_index,
        const u32  attribute_offset) {

        gl_context_clear_errors();

        constexpr u32       attribute_count         = 1;
        constexpr GLenum    attribute_type          = GL_INT;
        constexpr GLboolean attribute_is_normalized = GL_FALSE;
        const     void*     attribute_pointer       = (void*)((addr)attribute_offset);
        
        glVertexAttribPointer(
            attribute_index,
            attribute_count,
            attribute_type,
            attribute_is_normalized,
            vertex_size,
            attribute_pointer
        );

        vertex.error = glGetError();
        return(vertex.error == GL_ERROR_SUCCESS);
    }

    IFB_ENG_INTERNAL bool
    gl_vertex_attribute_set_f32 (
        gl_vertex& vertex,
        const u32  vertex_size,
        const u32  attribute_index,
        const u32  attribute_offset) {

        gl_context_clear_errors();

        constexpr u32       attribute_count         = 1;
        constexpr GLenum    attribute_type          = GL_FLOAT;
        constexpr GLboolean attribute_is_normalized = GL_FALSE;
        const     void*     attribute_pointer       = (void*)((addr)attribute_offset);
        
        glVertexAttribPointer(
            attribute_index,
            attribute_count,
            attribute_type,
            attribute_is_normalized,
            vertex_size,
            attribute_pointer
        );

        vertex.error = glGetError();
        return(vertex.error == GL_ERROR_SUCCESS);
    }
};