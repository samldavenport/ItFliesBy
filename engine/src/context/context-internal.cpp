#pragma once

#include "context.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    context_process_keycodes(
        context* ctx) {

        os_manager* os = (ctx != NULL) ? ctx->manager.os : NULL;
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
                        ctx->keymap_flags |= context_keymap_flag_e_devconsole;                       
                    } break;
                }
            }
        }
        
        if (window->input.keycodes.count_up > 0) {

            assert(
                window->input.keycodes.count_up <= OS_WINDOW_KEYCODE_CAPACITY &&
                window->input.keycodes.array_up != NULL              
            );

            for (
                u32 index = 0;
                index < window->input.keycodes.count_up;
                ++index) {

                const input_keycode keycode = window->input.keycodes.array_up[index];

                switch(keycode) {
                    
                    case (CONTEXT_KEYCODE_DEVTOOLS): {
                        if (ctx->keymap_flags & context_keymap_flag_e_devconsole) {
                            devconsole_toggle(ctx->devconsole);
                        }
                        ctx->keymap_flags &= ~context_keymap_flag_e_devconsole;                       
                    } break;
                }
            }
        }
    };
};