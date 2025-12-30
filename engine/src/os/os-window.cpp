#pragma once

#include "os-module.hpp"
#include "context.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    os_window_create_and_show(
        void) {

        os_window*  window = (_os_module != NULL) 
            ? _os_module->window
            : NULL;
        assert(window);

        // get monitor dimensions
        const os_monitor             monitor          = os_monitor_get_primary    ();
        const os_monitor_dimensions& monitor_dims     = os_monitor_get_dimensions (monitor);
        const u32                    monitor_center_x = os_monitor_get_center_x   (monitor_dims);
        const u32                    monitor_center_y = os_monitor_get_center_y   (monitor_dims);

        // configure window 
        os_window_config config;
        config.size.width  = OS_WINDOW_DEFAULT_WIDTH;
        config.size.height = OS_WINDOW_DEFAULT_HEIGHT;
        config.position.x  = monitor_center_x - (OS_WINDOW_DEFAULT_WIDTH  / 2); 
        config.position.y  = monitor_center_y - (OS_WINDOW_DEFAULT_HEIGHT / 2); 
        config.title       = "It Flies By";

        // create window handle
        window->handle = os_window_create(&config);
        assert(window->handle != NULL);

        // create graphics contexts
        window->opengl = os_window_init_opengl (window->handle);
        window->imgui  = os_window_init_imgui  (window->handle);
        assert(
            window->opengl != NULL &&
            window->imgui  != NULL            
        );

        // show the window and set other properties
        bool is_valid = true;
        is_valid &= os_window_get_size        (window->handle, &window->size);
        is_valid &= os_window_get_position    (window->handle, &window->position);
        is_valid &= os_window_show            (window->handle);
        assert(is_valid);
    }

    IFB_ENG_INTERNAL void
    os_window_start_frame_and_process_events(
        void) {

        os_window*  window = (_os_module != NULL) 
            ? _os_module->window
            : NULL;
        assert(window);

        bool is_valid = true;
        is_valid &= (window                  != NULL);
        is_valid &= (window->handle          != NULL);
        is_valid &= (window->size.height     != 0);   
        is_valid &= (window->size.width      != 0);   
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
                            window->flags |= os_window_flag_e_keydown; 
                        }
                    } break;
                    
                    case(os_window_event_type_e_key_up): {
                        if (key_up_index < OS_WINDOW_KEYCODE_CAPACITY) {
                            window->input.keycodes.array_up[key_up_index] = event.keycode;
                            ++key_up_index;
                            window->flags |= os_window_flag_e_keyup; 
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
        void) {

        os_window*  window = (_os_module != NULL) 
            ? _os_module->window
            : NULL;
        assert(window);

        bool can_render = true;
        can_render &= (window->handle != NULL);
        can_render &= (window->flags & os_window_flag_e_frame_started) != 0;
        assert(can_render);


        const bool did_render = sld::os_window_frame_render(window->handle);

        window->flags = (did_render)
            ? window->flags & ~(os_window_flag_e_frame_started)
            : window->flags & (os_window_flag_e_quit);
    }

    IFB_ENG_INTERNAL bool
    os_window_should_quit(
        void) {

        os_window*  window = (_os_module != NULL) 
            ? _os_module->window
            : NULL;
        assert(window);

        const bool should_quit = (window->flags & os_window_flag_e_quit);
        return(should_quit);
    }

    IFB_ENG_INTERNAL void
    os_window_reset_events(
        void) {

        os_window*  window = (_os_module != NULL) 
            ? _os_module->window
            : NULL;
        assert(window);

        assert(
            window                      != NULL                        &&
            window->event_list.array    != NULL                        &&
            window->event_list.count    <= window->event_list.capacity &&
            window->event_list.capacity <= OS_WINDOW_EVENT_CAPACITY 
        );

        constexpr u32 event_array_size = sizeof(os_window_event_type) * OS_WINDOW_EVENT_CAPACITY; 

        (void)memset((void*)window->event_list.array, os_window_event_type_e_unknown, event_array_size);

        window->event_list.count = 0;
    }

    IFB_ENG_INTERNAL void
    os_window_reset_input(
        void) {
        
        os_window*  window = (_os_module != NULL) 
            ? _os_module->window
            : NULL;
        assert(window);

        assert(
            window                            != NULL                       &&
            window->input.keycodes.array_down != NULL                       &&
            window->input.keycodes.array_up   != NULL                       &&
            window->input.keycodes.count_down <= OS_WINDOW_KEYCODE_CAPACITY &&
            window->input.keycodes.count_up   <= OS_WINDOW_KEYCODE_CAPACITY
        );

        constexpr u32 keycode_array_size = (sizeof(input_keycode) * OS_WINDOW_KEYCODE_CAPACITY);
        (void) memset ((void*)window->input.keycodes.array_down, input_keycode_e_null, keycode_array_size);
        (void) memset ((void*)window->input.keycodes.array_up,   input_keycode_e_null, keycode_array_size);
        
        window->input.keycodes.count_up   = 0;
        window->input.keycodes.count_down = 0;
        window->input.mouse.button        = os_window_mouse_button_e_none;
    }
};