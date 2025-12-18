#pragma once

#include "graphics.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL bool
    graphics_context_init(
        void) {

        bool     did_init   = true;
        gl_error init_error = GL_ERROR_SUCCESS;

        gl_context_init();
        
        gl_context_enable_depth_buffering(init_error);
        did_init &= (init_error == GL_ERROR_SUCCESS);

        gl_context_enable_smoothing(init_error);
        did_init &= (init_error == GL_ERROR_SUCCESS);

        return(did_init);
    }

};
