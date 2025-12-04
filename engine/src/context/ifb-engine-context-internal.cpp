#pragma once

#include "ifb-engine-context.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    context_process_keycodes(
        context* ctx) {

        os_context* os = (ctx != NULL) ? ctx->os : NULL;
        assert(os != NULL && os->window != NULL);

        os_window* window = os->window;

        if (window->input.keycodes.count_down > 0) {

            assert(
                window->input.keycodes.count_down <= OS_WINDOW_KEYCODE_CAPACITY &&
                window->input.keycodes.array_down != NULL              
            );

            for (
                u32 index = 0;
                index < window->input.keycodes.count_down;
                ++index) {

                const input_keycode keycode = window->input.keycodes.array_down[index];

                switch(keycode) {
                    
                    case (CONTEXT_KEYCODE_DEVTOOLS): {
                        ctx->flags.keymap |= context_keymap_flag_e_devtools;                       
                    } break;
                }
            }
        }
        
        if (window->input.keycodes.count_up > 0) {

        }

    };


};