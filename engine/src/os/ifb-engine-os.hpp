#ifndef IFB_ENGINE_PLATFORM_MANAGER_HPP
#define IFB_ENGINE_PLATFORM_MANAGER_HPP

#include "ifb-engine.hpp"

#include <sld-os.hpp> 
#include <sld-stack.hpp> 
#include <sld-array-list.hpp>

namespace ifb::eng {


    constexpr u32 OS_MAX_COUNT_MONITORS = IFB_ENG_CONFIG_OS_MAX_COUNT_MONITORS;
    constexpr u32 OS_MAX_COUNT_FILES    = IFB_ENG_CONFIG_OS_MAX_COUNT_FILES;

    struct os_manager;
    struct os_memory;
    struct os_window;
    struct os_monitor_table;
    struct os_file_table;
    struct os_file;

    struct os_file { u32 index; };
    struct os_file_list : array_list<os_file> { }; 

    struct os_monitor_table {
        u32                count;
        os_monitor_handle  primary_handle; 
        os_monitor_handle* os_handles;
    };

    struct os_window {
        os_window_handle window_handle;
    };

    struct os_file_table {
        os_file_handle* handle_array;
        os_file_list    file_list_open;
        os_file_list    file_list_closed;
    };

    struct os_memory {
        void* reservation_start;
        u64   reservation_size_kb;
    };

    struct os_system_info {
        os_system_memory_info    memory;
        os_system_cpu_info       cpu;
        os_system_cpu_cache_info cpu_cache_l1;
        os_system_cpu_cache_info cpu_cache_l2;
        os_system_cpu_cache_info cpu_cache_l3;
    };

    struct os_manager {
        os_system_info*   system_info;
        os_window*        window;
        os_monitor_table* monitor_table;
        os_file_table*    file_table;
    };

    IFB_ENG_INTERNAL os_manager* os_manager_stack_alloc (stack& stack);
    IFB_ENG_INTERNAL void        os_manager_startup     (os_manager* mngr);
    IFB_ENG_INTERNAL void        os_manager_shutdown    (os_manager* mngr);


};

#endif //IFB_ENGINE_PLATFORM_MANAGER_HPP