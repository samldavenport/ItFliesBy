#pragma once

#include "context.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    context_process_keycodes(
        context* ctx) {

        const os_window_input& input = os_window_get_input();

        if (input.keycodes.count_down > 0) {

            assert(
                input.keycodes.count_down <= OS_WINDOW_KEYCODE_CAPACITY &&
                input.keycodes.array_down != NULL
            );

            for (
                u32 index = 0;
                index < input.keycodes.count_down;
                ++index) {

                const input_keycode keycode = input.keycodes.array_down[index];

                switch(keycode) {
                    
                    case (CONTEXT_KEYCODE_DEVTOOLS): {
                        ctx->keymap_flags |= context_keymap_flag_e_devconsole;                       
                    } break;
                }
            }
        }
        
        if (input.keycodes.count_up > 0) {

            assert(
                input.keycodes.count_up <= OS_WINDOW_KEYCODE_CAPACITY &&
                input.keycodes.array_up != NULL              
            );

            for (
                u32 index = 0;
                index < input.keycodes.count_up;
                ++index) {

                const input_keycode keycode = input.keycodes.array_up[index];

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