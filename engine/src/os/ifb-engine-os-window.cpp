#pragma once

#include "ifb-engine-os.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    os_window_create_and_show(
        os_context* os) {

        assert(
            os         != NULL &&
            os->window != NULL
        );
        os_window* window = os->window;
        
        // get monitor dimensions
        const os_monitor_dimensions* monitor_dims = os_monitor_get_primrary_dimensions(os);
        assert(monitor_dims != NULL);

        // configure window 
        os_window_config config;
        config.position.x  = monitor_dims->virtual_position_x + (monitor_dims->pixel_width  / 2);
        config.position.y  = monitor_dims->virtual_position_y + (monitor_dims->pixel_height / 2);
        config.size.width  = 1024;
        config.size.height = 768;
        config.title       = "It Flies By";

        // create window handle
        window->handle = os_window_create(&config);
        assert(window->handle != NULL);

        // set the viewport
        window->viewport.pos_x  = 0;
        window->viewport.pos_y  = 0;
        window->viewport.width  = config.size.width;
        window->viewport.height = config.size.height;
        (void)os_window_set_viewport(
            window->handle,
            &window->viewport);

        // show the window and set other properties
        (void)os_window_show     (window->handle);
        (void)os_window_get_size (window->handle, &window->size);
    }

    IFB_ENG_INTERNAL void
    os_window_start_frame_and_process_events(
        os_context* os) {

        os_window* window = (os != NULL) ? os->window : NULL;

        bool is_valid = true;
        is_valid &= (window                  != NULL);
        is_valid &= (window->handle          != NULL);
        is_valid &= (window->size.height     != 0);   
        is_valid &= (window->size.width      != 0);   
        is_valid &= (window->viewport.height != 0);   
        is_valid &= (window->viewport.width  != 0);   
        is_valid &= ((window->flags & os_window_flag_e_frame_started) == 0); 
        assert(is_valid);

        const bool did_start_frame = sld::os_window_frame_start(window->handle);
        if (did_start_frame) {
            window->flags |= os_window_flag_e_frame_started;
        }

        const bool did_process_events = sld::os_window_process_events(
            window->handle,
            &window->event_list
        );

        if (did_process_events && window->event_list.count > 0) {

            assert(
                window->event_list.count          <= window->event_list.capacity &&
                window->event_list.array          != NULL &&
                window->input.keycodes.array_down != NULL &&
                window->input.keycodes.array_up   != NULL
            );

            window->input.keycodes.count_down = 0;
            window->input.keycodes.count_up   = 0;

            u32& key_down_index = window->input.keycodes.count_down;
            u32& key_up_index   = window->input.keycodes.count_up;

            for (
                u32 event_index = 0;
                    event_index < window->event_list.count;
                  ++event_index) {

                const os_window_event& event = window->event_list.array[event_index];

                switch(event.type) {

                    case(os_window_event_type_e_resized): {
                        window->size   = event.window_size;
                        window->flags &= os_window_flag_e_viewport_changed; 
                    } break;
                    
                    case(os_window_event_type_e_moved): {
                        window->position = event.window_position;
                    } break;
                    
                    case(os_window_event_type_e_key_down): {
                        if (key_down_index < OS_WINDOW_KEYCODE_CAPACITY) {
                            window->input.keycodes.array_down[key_down_index] = event.keycode;
                            ++key_down_index;
                            window->flags &= os_window_flag_e_keydown; 
                        }
                    } break;
                    
                    case(os_window_event_type_e_key_up): {
                        if (key_up_index < OS_WINDOW_KEYCODE_CAPACITY) {
                            window->input.keycodes.array_up[key_up_index] = event.keycode;
                            ++key_up_index;
                            window->flags &= os_window_flag_e_keyup; 
                        }
                    } break;

                    case(os_window_event_type_e_mouse_left_up): {
                        window->input.mouse.button  = os_window_mouse_button_e_left_up;
                        window->flags              |= os_window_flag_e_mouse_button_clicked;
                    } break;

                    case(os_window_event_type_e_mouse_left_down): {
                        window->input.mouse.button  = os_window_mouse_button_e_left_down;
                        window->flags              |= os_window_flag_e_mouse_button_clicked;
                    } break;

                    case(os_window_event_type_e_mouse_left_dbl_click): {
                        window->input.mouse.button  = os_window_mouse_button_e_left_double_click;
                        window->flags              |= os_window_flag_e_mouse_button_clicked;
                    } break;

                    case(os_window_event_type_e_mouse_right_up): {
                        window->input.mouse.button  = os_window_mouse_button_e_right_up;
                        window->flags              |= os_window_flag_e_mouse_button_clicked;
                    } break;

                    case(os_window_event_type_e_mouse_right_down): {
                        window->input.mouse.button  = os_window_mouse_button_e_right_down;
                        window->flags              |= os_window_flag_e_mouse_button_clicked;
                    } break;

                    case(os_window_event_type_e_mouse_right_dbl_click): {
                        window->input.mouse.button  = os_window_mouse_button_e_right_double_click;
                        window->flags              |= os_window_flag_e_mouse_button_clicked;
                    } break;

                    case(os_window_event_type_e_quit):
                    case(os_window_event_type_e_destroyed): {
                        window->flags |= os_window_flag_e_quit;
                    } break;

                    default: break;
                }
            }

            assert(
                window->input.keycodes.count_down <= OS_WINDOW_KEYCODE_CAPACITY && 
                window->input.keycodes.count_up   <= OS_WINDOW_KEYCODE_CAPACITY
            );
        }
    }

    IFB_ENG_INTERNAL void
    os_window_render_frame(
        os_context* os) {

        os_window* window = (os != NULL) ? os->window : NULL;

        assert(
            window                                           != NULL &&
            window->handle                                   != NULL &&
            (window->flags & os_window_flag_e_frame_started) != 0
        );

        const bool did_render = sld::os_window_frame_render(window->handle);

        window->flags = (did_render)
            ? window->flags & ~(os_window_flag_e_frame_started)
            : window->flags & (os_window_flag_e_quit);
    }
};