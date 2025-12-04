#pragma once

#include "ifb-engine-context.hpp"
#include "ifb-engine-os.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void              os_context_assert_valid        (const os_context* os_mngr);
    IFB_ENG_INTERNAL os_window*        os_context_alloc_window        (stack& stack); 
    IFB_ENG_INTERNAL os_monitor_table* os_context_alloc_monitor_table (stack& stack); 
    IFB_ENG_INTERNAL os_file_table*    os_context_alloc_file_table    (stack& stack); 
    IFB_ENG_INTERNAL os_memory*        os_context_alloc_memory        (stack& stack); 
    IFB_ENG_INTERNAL os_system_info*   os_context_alloc_system_info   (stack& stack); 

    IFB_ENG_INTERNAL os_context*
    os_context_alloc(
        stack& stack) {

        auto context = stack.push_struct<os_context>();
        assert(context != NULL);

        // members
        context->window        = os_context_alloc_window        (stack);
        context->monitor_table = os_context_alloc_monitor_table (stack);
        context->file_table    = os_context_alloc_file_table    (stack);
        context->memory        = os_context_alloc_memory        (stack);
        context->system_info   = os_context_alloc_system_info   (stack);

        return(context);
    }

    IFB_ENG_INTERNAL void
    os_context_init(
        os_context* os) {

        os_context_assert_valid   (os);
        os_system_refresh_info    (os);
        os_memory_reserve         (os);
        os_monitor_refresh_table  (os);
        os_window_create_and_show (os);
    }

    IFB_ENG_INTERNAL void
    os_context_refresh_system_info(
        os_context* os) {

        os_system_refresh_info   (os);
        os_monitor_refresh_table (os);
        os_memory_check_usage    (os);
    }

    IFB_ENG_INTERNAL bool
    os_context_frame_start(
        os_context* os) {

        assert(os);

        os_window_start_frame_and_process_events(os);


        return(true);


    }

    IFB_ENG_INTERNAL bool
    os_context_frame_render(
        os_context* os) {

        assert(os);
        
        os_window_render_frame(os);

        return(true);
    }

    IFB_ENG_INTERNAL void
    os_context_destroy(
        os_context* mngr) {

    }

    IFB_ENG_INTERNAL os_window*
    os_context_alloc_window(
        stack& stack) {

        auto window        = stack.push_struct<os_window>         ();
        auto events        = stack.push_struct<os_window_event>   (OS_WINDOW_EVENT_CAPACITY);
        auto keycodes_up   = stack.push_struct<os_window_keycode> (OS_WINDOW_KEYCODE_CAPACITY);
        auto keycodes_down = stack.push_struct<os_window_keycode> (OS_WINDOW_KEYCODE_CAPACITY);

        assert(
            window        != NULL &&
            events        != NULL &&
            keycodes_up   != NULL &&
            keycodes_down != NULL
        );

        window->handle                    = NULL;
        window->position.x                = 0;
        window->position.y                = 0;
        window->size.width                = 0;
        window->size.height               = 0;
        window->viewport.pos_x            = 0;
        window->viewport.pos_y            = 0;
        window->viewport.width            = 0;
        window->viewport.height           = 0;
        window->event_list.array          = events;
        window->event_list.capacity       = OS_WINDOW_EVENT_CAPACITY;  
        window->event_list.count          = 0;
        window->flags                     = os_window_flag_e_none;
        window->input.mouse.position.x    = 0;
        window->input.mouse.position.y    = 0;
        window->input.mouse.button        = os_window_mouse_button_e_none;
        window->input.keycodes.array_down = keycodes_down;
        window->input.keycodes.array_up   = keycodes_up;
        window->input.keycodes.count_down = 0;
        window->input.keycodes.count_up   = 0;

        return(window);
    }
    
    IFB_ENG_INTERNAL os_monitor_table*
    os_context_alloc_monitor_table(
        stack& stack) {

        auto monitor_table = stack.push_struct<os_monitor_table>      ();
        auto handles       = stack.push_struct<os_monitor_handle>     (OS_MONITOR_MAX_COUNT);
        auto dimensions    = stack.push_struct<os_monitor_dimensions> (OS_MONITOR_MAX_COUNT);
        auto names         = stack.push_struct<os_monitor_name>       (OS_MONITOR_MAX_COUNT);
        assert(
            monitor_table != NULL &&
            handles       != NULL &&
            dimensions    != NULL &&
            names         != NULL
        );

        monitor_table->count                             = 0;
        monitor_table->primary                           = OS_MONITOR_INVALID;
        monitor_table->working_area.virtual_pixel_width  = 0; 
        monitor_table->working_area.virtual_pixel_height = 0; 
        monitor_table->array.handles                     = handles;
        monitor_table->array.dimensions                  = dimensions;
        monitor_table->array.names                       = names;

        return(monitor_table); 
    }
    
    IFB_ENG_INTERNAL os_file_table*
    os_context_alloc_file_table(
        stack& stack) {

        auto file_table   = stack.push_struct<os_file_table>();
        auto handle_array = stack.push_struct<os_file_handle>(OS_FILE_MAX_COUNT); 
        assert(
            file_table   != NULL &&
            handle_array != NULL
        );

        for (
            os_file file = 0;
            file < OS_FILE_MAX_COUNT;
            ++file) {

            handle_array[file] = NULL;
        }

        file_table->handle_array = handle_array;
        return(file_table);
    }
    
    IFB_ENG_INTERNAL os_memory*
    os_context_alloc_memory(
        stack& stack) {

        auto memory = stack.push_struct<os_memory>();
        assert(memory);
        return(memory);
    }
    
    IFB_ENG_INTERNAL os_system_info*
    os_context_alloc_system_info(
        stack& stack) {

        auto sys_info = stack.push_struct<os_system_info>();
        assert(sys_info);

        return(sys_info);
    }

    IFB_ENG_INTERNAL void
    os_context_assert_valid(
        const os_context* os_mngr) {

        assert(
            os_mngr                != NULL &&
            os_mngr->system_info   != NULL &&
            os_mngr->memory        != NULL &&
            os_mngr->file_table    != NULL &&
            os_mngr->monitor_table != NULL &&
            os_mngr->window        != NULL
        );
    }
};