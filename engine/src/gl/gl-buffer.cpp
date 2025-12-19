#pragma once

#include "gl.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    gl_buffer_create(
        gl_buffer& buffer) {

        gl_context_clear_errors();

        buffer.error = GL_ERROR_SUCCESS;
        glCreateBuffers(1, &buffer.id);

        assert(buffer.is_valid());
    }

    IFB_ENG_INTERNAL void
    gl_buffer_destroy(
        gl_buffer& buffer) {

        gl_context_clear_errors();
        glDeleteBuffers(1, &buffer.id);
        // TODO(sam): get buffer delete status
        assert(glGetError() == GL_ERROR_SUCCESS);
        buffer.reset();
    }
};