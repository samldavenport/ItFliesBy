#pragma once

#include "context.hpp"
#include "os-module.hpp"
#include "memory.hpp"

namespace ifb::eng {

    static os_module* _os_module;

    IFB_ENG_INTERNAL os_module*
    os_module_init(
        void) {

        // stack allocate
        auto module               = memory_stack_alloc_struct <os_module>             ();
        auto window               = memory_stack_alloc_struct <os_window>             ();
        auto window_events        = memory_stack_alloc_struct <os_window_event>       (OS_WINDOW_EVENT_CAPACITY);
        auto window_keycodes_up   = memory_stack_alloc_struct <os_window_keycode>     (OS_WINDOW_KEYCODE_CAPACITY);
        auto window_keycodes_down = memory_stack_alloc_struct <os_window_keycode>     (OS_WINDOW_KEYCODE_CAPACITY);
        auto monitor_table        = memory_stack_alloc_struct <os_monitor_table>      ();
        auto monitor_handles      = memory_stack_alloc_struct <os_monitor_handle>     (OS_MONITOR_MAX_COUNT);
        auto monitor_dimensions   = memory_stack_alloc_struct <os_monitor_dimensions> (OS_MONITOR_MAX_COUNT);
        auto monitor_names        = memory_stack_alloc_struct <os_monitor_name>       (OS_MONITOR_MAX_COUNT);
        auto file_table           = memory_stack_alloc_struct <os_file_table>         ();
        auto file_handle_array    = memory_stack_alloc_struct <os_file_handle>        (OS_FILE_MAX_COUNT); 
        auto memory               = memory_stack_alloc_struct <os_memory>             ();
        auto sys_info             = memory_stack_alloc_struct <os_system>             ();

        // check allocations
        bool is_valid = true;
        is_valid &= (module               != NULL);
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
        window->handle                    = NULL;
        window->position.x                = 0;
        window->position.y                = 0;
        window->size.width                = 0;
        window->size.height               = 0;
        window->event_list.array          = window_events;
        window->event_list.capacity       = OS_WINDOW_EVENT_CAPACITY;  
        window->event_list.count          = 0;
        window->flags                     = os_window_flag_e_none;
        window->input.mouse.position.x    = 0;
        window->input.mouse.position.y    = 0;
        window->input.mouse.button        = os_window_mouse_button_e_none;
        window->input.keycodes.array_down = window_keycodes_down;
        window->input.keycodes.array_up   = window_keycodes_up;
        window->input.keycodes.count_down = 0;
        window->input.keycodes.count_up   = 0;

        // monitors
        monitor_table->count                             = 0;
        monitor_table->primary                           = OS_MONITOR_INVALID;
        monitor_table->working_area.virtual_pixel_width  = 0; 
        monitor_table->working_area.virtual_pixel_height = 0; 
        monitor_table->array.handles                     = monitor_handles;
        monitor_table->array.dimensions                  = monitor_dimensions;
        monitor_table->array.names                       = monitor_names;

        // files
        file_table->handle_array = file_handle_array;
        for (
            os_file file = 0;
            file < OS_FILE_MAX_COUNT;
            ++file) {

            file_handle_array[file] = NULL;
        }

        // module
        module->window        = window; 
        module->monitor_table = monitor_table;
        module->file_table    = file_table;
        module->memory        = memory;
        module->system        = sys_info;

        _os_module = module;
        return(_os_module);
    }
};