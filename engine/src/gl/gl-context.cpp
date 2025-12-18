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
};