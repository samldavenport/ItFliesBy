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
        os_context* mngr) {

        os_context_assert_valid   (mngr);
        os_system_refresh_info    (mngr);
        os_memory_reserve         (mngr);
        os_monitor_init_table     (mngr);
        os_window_create_and_show (mngr);
    }

    IFB_ENG_INTERNAL void
    os_context_destroy(
        os_context* mngr) {

    }


    IFB_ENG_INTERNAL os_window*
    os_context_alloc_window(
        stack& stack) {

        auto window = stack.push_struct<os_window>      ();
        auto events = stack.push_struct<os_window_event>(OS_WINDOW_EVENT_CAPACITY);
        
        assert(
            window &&
            events
        );

        window->event_list.array    = events;
        window->event_list.capacity = OS_WINDOW_EVENT_CAPACITY;  
        window->event_list.count    = 0;  

        return(window);
    }
    
    IFB_ENG_INTERNAL os_monitor_table*
    os_context_alloc_monitor_table(
        stack& stack) {

        auto monitor_table = stack.push_struct<os_monitor_table>      ();
        auto handles       = stack.push_struct<os_monitor_handle>     (OS_MAX_COUNT_MONITORS);
        auto dimensions    = stack.push_struct<os_monitor_dimensions> (OS_MAX_COUNT_MONITORS);
        auto names         = stack.push_struct<os_monitor_name>       (OS_MAX_COUNT_MONITORS);
        assert(
            monitor_table != NULL &&
            handles       != NULL &&
            dimensions    != NULL &&
            names         != NULL
        );
        return(monitor_table); 
    }
    
    IFB_ENG_INTERNAL os_file_table*
    os_context_alloc_file_table(
        stack& stack) {

        auto file_table   = stack.push_struct<os_file_table>();
        auto handle_array = stack.push_struct<os_file_handle>(OS_MAX_COUNT_FILES); 
        assert(
            file_table   != NULL &&
            handle_array != NULL
        );
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