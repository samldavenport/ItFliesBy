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
        assert(
            manager->system_info   != NULL &&
            manager->window        != NULL &&
            manager->monitor_table != NULL &&
            manager->file_table    != NULL
        );

        // monitor_table
        os_monitor_table* monitor_table = manager->monitor_table;
        monitor_table->os_handles = stack.push_struct<os_monitor_handle>(OS_MAX_COUNT_MONITORS); 
        assert(monitor_table->os_handles != NULL);

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


};