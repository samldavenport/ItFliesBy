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
};