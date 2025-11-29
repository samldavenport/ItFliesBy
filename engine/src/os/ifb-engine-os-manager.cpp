#pragma once

#include "ifb-engine-context.hpp"
#include "ifb-engine-os.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL os_window*        os_manager_alloc_window        (stack& stack); 
    IFB_ENG_INTERNAL os_monitor_table* os_manager_alloc_monitor_table (stack& stack); 
    IFB_ENG_INTERNAL os_file_table*    os_manager_alloc_file_table    (stack& stack); 
    IFB_ENG_INTERNAL os_memory*        os_manager_alloc_memory        (stack& stack); 
    IFB_ENG_INTERNAL os_system_info*   os_manager_alloc_system_info   (stack& stack); 

    IFB_ENG_INTERNAL void
    os_manager_alloc(
        void) {

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
    }

    IFB_ENG_INTERNAL void
    os_manager_startup(
        void) {

        os_manager_assert_valid(mngr);
        os_manager_system_info_refresh()

        // reserve memory equal to half of the installed RAM
        os_memory* memory = mngr->memory;
        memory->reservation_size  = size_kilobytes    (system_info->memory.installed_ram_size_kb) / 2;
        memory->reservation_start = os_memory_reserve (NULL, memory->reservation_size);
        memory->committed_size    = 0;
        os_memory_assert_valid(memory);

        // get the monitor info
        os_monitor_table* monitor_table = mngr->monitor_table;
        monitor_table->count          = os_monitor_count();
        assert(monitor_table->count <= OS_MAX_COUNT_MONITORS);
        const os_monitor_handle primary_monitor_handle = os_monitor_get_primary(); 
        os_monitor_get_working_area(monitor_table->working_area);
        os_monitor_info monitor_info;
        for (
            u32 monitor = 0;
                monitor < monitor_table->count;
              ++monitor) {

            memset(&monitor_info, 0, sizeof(monitor_info));
            monitor_info.index = monitor;
            os_monitor_get_info(monitor_info);

            monitor_table->array.handles    [monitor] = monitor_info.handle;
            monitor_table->array.dimensions [monitor] = monitor_info.dimensions;
            monitor_table->array.names      [monitor] = monitor_info.name;

            if (primary_monitor_handle.val == monitor_info.handle.val) {
                monitor_table->primary.index = monitor;
            }
        }
        os_monitor_table_assert_valid(monitor_table);

        // initialize the file table
        os_file_table* file_table = mngr->file_table;
        file_table->file_list_closed.reset();
        file_table->file_list_open.reset();

        for (
            os_file file = {0};
                    file.index < OS_MAX_COUNT_FILES;
                  ++file.index) {
            
            file_table->handle_array[file.index].val = NULL;
            assert(file_table->file_list_closed.add(file));
        }
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
};