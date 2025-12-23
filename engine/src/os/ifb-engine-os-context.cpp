#pragma once

#include "ifb-engine-context.hpp"
#include "ifb-engine-os.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL os_context*
    os_context_alloc(
        stack& stack) {

        // stack allocate
        auto context              = stack.push_struct<os_context>            ();
        auto window               = stack.push_struct<os_window>             ();
        auto window_events        = stack.push_struct<os_window_event>       (OS_WINDOW_EVENT_CAPACITY);
        auto window_keycodes_up   = stack.push_struct<os_window_keycode>     (OS_WINDOW_KEYCODE_CAPACITY);
        auto window_keycodes_down = stack.push_struct<os_window_keycode>     (OS_WINDOW_KEYCODE_CAPACITY);
        auto monitor_table        = stack.push_struct<os_monitor_table>      ();
        auto monitor_handles      = stack.push_struct<os_monitor_handle>     (OS_MONITOR_MAX_COUNT);
        auto monitor_dimensions   = stack.push_struct<os_monitor_dimensions> (OS_MONITOR_MAX_COUNT);
        auto monitor_names        = stack.push_struct<os_monitor_name>       (OS_MONITOR_MAX_COUNT);
        auto file_table           = stack.push_struct<os_file_table>         ();
        auto file_handle_array    = stack.push_struct<os_file_handle>        (OS_FILE_MAX_COUNT); 
        auto memory               = stack.push_struct<os_memory>             ();
        auto sys_info             = stack.push_struct<os_system_info>        ();

        // check allocations
        bool is_valid = true;
        is_valid &= (context              != NULL);
        is_valid &= (window               != NULL);
        is_valid &= (window_events        != NULL);
        is_valid &= (window_keycodes_up   != NULL);
        is_valid &= (window_keycodes_down != NULL);
        is_valid &= (monitor_table        != NULL);
        is_valid &= (monitor_handles      != NULL);
        is_valid &= (monitor_dimensions   != NULL);
        is_valid &= (monitor_names        != NULL);
        is_valid &= (file_table           != NULL);
        is_valid &= (file_handle_array    != NULL);
        is_valid &= (memory               != NULL);
        is_valid &= (sys_info             != NULL);
        assert(is_valid);

        // window
        window->handle                                   = NULL;
        window->position.x                               = 0;
        window->position.y                               = 0;
        window->size.width                               = 0;
        window->size.height                              = 0;
        window->event_list.array                         = window_events;
        window->event_list.capacity                      = OS_WINDOW_EVENT_CAPACITY;  
        window->event_list.count                         = 0;
        window->flags                                    = os_window_flag_e_none;
        window->input.mouse.position.x                   = 0;
        window->input.mouse.position.y                   = 0;
        window->input.mouse.button                       = os_window_mouse_button_e_none;
        window->input.keycodes.array_down                = window_keycodes_down;
        window->input.keycodes.array_up                  = window_keycodes_up;
        window->input.keycodes.count_down                = 0;
        window->input.keycodes.count_up                  = 0;

        // monitors
        monitor_table->count                             = 0;
        monitor_table->primary                           = OS_MONITOR_INVALID;
        monitor_table->working_area.virtual_pixel_width  = 0; 
        monitor_table->working_area.virtual_pixel_height = 0; 
        monitor_table->array.handles                     = monitor_handles;
        monitor_table->array.dimensions                  = monitor_dimensions;
        monitor_table->array.names                       = monitor_names;

        // files
        file_table->handle_array                         = file_handle_array;
        for (
            os_file file = 0;
            file < OS_FILE_MAX_COUNT;
            ++file) {

            file_handle_array[file] = NULL;
        }

        // context
        context->window                                  = window; 
        context->monitor_table                           = monitor_table;
        context->file_table                              = file_table;
        context->memory                                  = memory;
        context->system_info                             = sys_info;

        return(context);
    }
};