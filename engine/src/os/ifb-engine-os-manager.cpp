#pragma once

#include "ifb-engine-context.hpp"
#include "ifb-engine-os.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void              os_manager_assert_valid        (void);
    IFB_ENG_INTERNAL os_window*        os_manager_alloc_window        (stack& stack); 
    IFB_ENG_INTERNAL os_monitor_table* os_manager_alloc_monitor_table (stack& stack); 
    IFB_ENG_INTERNAL os_file_table*    os_manager_alloc_file_table    (stack& stack); 
    IFB_ENG_INTERNAL os_memory*        os_manager_alloc_memory        (stack& stack); 
    IFB_ENG_INTERNAL os_system_info*   os_manager_alloc_system_info   (stack& stack); 

    IFB_ENG_INTERNAL os_manager*
    os_manager_alloc(
        stack& stack) {

        auto& stack = _context->stack;

        // os manager
        auto manager = stack.push_struct<os_manager>(stack);
        assert(manager != NULL);
        _context->os_mngr

        // members
        manager->window        = os_manager_alloc_window        (stack);
        manager->monitor_table = os_manager_alloc_monitor_table (stack);
        manager->file_table    = os_manager_alloc_file_table    (stack);
        manager->memory        = os_manager_alloc_memory        (stack);
        manager->system_info   = os_manager_alloc_system_info   (stack);

        return(manager);
    }

    IFB_ENG_INTERNAL void
    os_manager_startup(
        os_manager* mngr) {

        os_manager_assert_valid        (mngr);
        os_manager_system_info_refresh (mngr);


    }

    IFB_ENG_INTERNAL void
    os_manager_shutdown(
        os_manager* mngr) {

    }



    IFB_ENG_INTERNAL os_window*
    os_manager_alloc_window(
        stack& stack) {

        auto window = stack.push_struct<os_window>();
        assert(window);
        return(window);
    }
    
    IFB_ENG_INTERNAL os_monitor_table*
    os_manager_alloc_monitor_table(
        stack& stack) {

        auto monitor_table = stack.push_struct<os_monitor_table>();
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
    os_manager_alloc_file_table(
        stack& stack) {

        auto file_table   = stack.push_struct<os_file_table>();
        auto handle_array = stack.push_struct<os_file_handle>(OS_MAX_COUNT_FILES); 
        assert(
            file_table &&
            file_handles
        );
        file_table->handle_array = handle_array;
        return(file_table);
    }
    
    IFB_ENG_INTERNAL os_memory*
    os_manager_alloc_memory(
        stack& stack) {

        auto memory = stack.push_struct<os_memory>();
        assert(memory);
        return(memory);
    }
    
    IFB_ENG_INTERNAL os_system_info*
    os_manager_alloc_system_info(
        stack& stack) {

        auto sys_info = stack.push_struct<os_system_info>();
        assert(sys_info);
    }

    IFB_ENG_INTERNAL void
    os_manager_assert_valid(
        const os_manager* os_mngr) {

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