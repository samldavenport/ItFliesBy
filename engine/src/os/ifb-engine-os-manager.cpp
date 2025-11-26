#pragma once

#include "ifb-engine-os.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL os_manager*
    os_manager_stack_alloc(
        stack& stack) {

        // os manager
        auto manager = stack.push_struct<os_manager>();
        assert(manager != NULL);

        // members
        manager->system_info   = stack.push_struct<os_system_info>();
        manager->window        = stack.push_struct<os_window>();
        manager->monitor_table = stack.push_struct<os_monitor_table>();
        manager->file_table    = stack.push_struct<os_file_table>();
        manager->memory        = stack.push_struct<os_memory>();
        assert(
            manager->system_info   != NULL &&
            manager->window        != NULL &&
            manager->monitor_table != NULL &&
            manager->file_table    != NULL &&
            manager->memory        != NULL
        );

        // monitor_table
        os_monitor_table* monitor_table = manager->monitor_table;
        monitor_table->array.handles    = stack.push_struct<os_monitor_handle>    (OS_MAX_COUNT_MONITORS); 
        monitor_table->array.dimensions = stack.push_struct<os_monitor_dimensions>(OS_MAX_COUNT_MONITORS); 
        monitor_table->array.names      = stack.push_struct<os_monitor_name>      (OS_MAX_COUNT_MONITORS); 
        assert(
            monitor_table->array.handles    != NULL &&
            monitor_table->array.dimensions != NULL &&
            monitor_table->array.names      != NULL
        );

        // file table
        os_file_table* file_table = manager->file_table;
        file_table->handle_array   = stack.push_struct<os_file_handle>(OS_MAX_COUNT_FILES);
        os_file* file_array_open   = stack.push_struct<os_file>       (OS_MAX_COUNT_FILES);
        os_file* file_array_closed = stack.push_struct<os_file>       (OS_MAX_COUNT_FILES);
        assert(
            file_table->handle_array != NULL &&
            file_array_open                  &&
            file_array_closed
        );
        file_table->file_list_open.init   (file_array_open, OS_MAX_COUNT_FILES);
        file_table->file_list_closed.init (file_array_open, OS_MAX_COUNT_FILES);

        return(manager);
    }

    IFB_ENG_INTERNAL void
    os_manager_startup(
        os_manager* mngr) {

        os_manager_assert_valid(mngr);

        // get system info
        os_system_info* system_info = mngr->system_info;
        os_system_get_cpu_info       (system_info->cpu);
        os_system_get_memory_info    (system_info->memory);
        os_system_get_cpu_cache_info (system_info->cpu_cache_l1);
        os_system_get_cpu_cache_info (system_info->cpu_cache_l2);
        os_system_get_cpu_cache_info (system_info->cpu_cache_l3);
        os_system_info_assert_valid(system_info);

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
        monitor_table->primary_handle = os_monitor_get_primary(); 
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
        }

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

};