#ifndef IFB_ENGINE_PLATFORM_MANAGER_HPP
#define IFB_ENGINE_PLATFORM_MANAGER_HPP

#include "ifb-engine.hpp"

#include <sld-os.hpp> 
#include <sld-stack.hpp> 
#include <sld-array-list.hpp>

namespace ifb::eng {

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr u32 OS_MAX_COUNT_FILES    = IFB_ENG_CONFIG_OS_MAX_COUNT_FILES;
    constexpr u32 OS_MAX_COUNT_MONITORS = IFB_ENG_CONFIG_OS_MAX_COUNT_MONITORS;
    constexpr u32 OS_FILE_INVALID       = OS_MAX_COUNT_FILES; 
    constexpr u32 OS_MONITOR_INVALID    = OS_MAX_COUNT_MONITORS; 

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct os_manager;
    struct os_memory;
    struct os_window;
    struct os_monitor_table;
    struct os_file_table;

    using os_file    = u32;
    using os_monitor = u32;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL os_manager* os_manager_alloc                 (stack& stack);
    IFB_ENG_INTERNAL void        os_manager_startup               (os_manager* os_mngr);
    IFB_ENG_INTERNAL void        os_manager_shutdown              (os_manager* os_mngr);
    IFB_ENG_INTERNAL void        os_manager_system_info_refresh   (os_manager* os_mngr);
    IFB_ENG_INTERNAL void        os_manager_memory_reserve        (os_manager* os_mngr, const u64 size, const u64 alignment);
    IFB_ENG_INTERNAL void        os_manager_memory_release        (os_manager* os_mngr);
    IFB_ENG_INTERNAL void        os_manager_memory_commit         (os_manager* os_mngr, const u64 size);
    IFB_ENG_INTERNAL void        os_manager_memory_decommit       (os_manager* os_mngr, const void* start, const u64 size);
    IFB_ENG_INTERNAL void        os_manager_monitor_table_refresh (os_manager* os_manager);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct os_manager {
        os_system_info*   system_info;
        os_window*        window;
        os_monitor_table* monitor_table;
        os_file_table*    file_table;
        os_memory*        memory;
    };

    struct os_system_info {
        os_system_memory_info    memory;
        os_system_cpu_info       cpu;
        os_system_cpu_cache_info cpu_cache_l1;
        os_system_cpu_cache_info cpu_cache_l2;
        os_system_cpu_cache_info cpu_cache_l3;
    };

    struct os_monitor_table {
        u32                     count;
        os_monitor              primary; 
        os_monitor_working_area working_area;
        struct {
            os_monitor_handle*      handles;
            os_monitor_dimensions*  dimensions;
            os_monitor_name*        names;
        } array;
    };

    struct os_window {
        os_window_handle window_handle;
    };

    struct os_file_table {
        os_file_handle* handle_array;
    };

    struct os_memory {
        addr reservation_start;
        u64  reservation_size;
        u64  committed_size;
        u64  alignment;
    };




};

#endif //IFB_ENGINE_PLATFORM_MANAGER_HPP