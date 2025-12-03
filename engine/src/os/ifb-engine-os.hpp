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

    constexpr u32 OS_MAX_COUNT_FILES       = IFB_ENG_CONFIG_OS_MAX_COUNT_FILES;
    constexpr u32 OS_MAX_COUNT_MONITORS    = IFB_ENG_CONFIG_OS_MAX_COUNT_MONITORS;
    constexpr u32 OS_FILE_INVALID          = OS_MAX_COUNT_FILES; 
    constexpr u32 OS_MONITOR_INVALID       = OS_MAX_COUNT_MONITORS; 
    constexpr u32 OS_WINDOW_EVENT_CAPACITY = IFB_ENG_CONFIG_OS_WINDOW_EVENT_CAPACITY;

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct os_context;
    struct os_memory;
    struct os_window;
    struct os_monitor_table;
    struct os_file_table;
    struct os_system_info;

    using os_file    = u32;
    using os_monitor = u32;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    // context
    IFB_ENG_INTERNAL os_context*                  os_context_alloc                  (stack& stack);
    IFB_ENG_INTERNAL void                         os_context_init                   (os_context* os);
    IFB_ENG_INTERNAL void                         os_context_destroy                (os_context* os);

    // memory
    IFB_ENG_INTERNAL void                         os_memory_reserve                 (os_context* os);
    IFB_ENG_INTERNAL void                         os_memory_release                 (os_context* os);
    IFB_ENG_INTERNAL void*                        os_memory_commit                  (os_context* os, const u64   start, const u64 size);
    IFB_ENG_INTERNAL void                         os_memory_decommit                (os_context* os, void* start, const u64 size);
    IFB_ENG_INTERNAL bool                         os_memory_is_page_aligned         (os_context* os, const u64   start);

    // monitors
    IFB_ENG_INTERNAL void                         os_monitor_init_table              (os_context* os);
    IFB_ENG_INTERNAL const os_monitor_dimensions* os_monitor_get_primrary_dimensions (os_context* os);

    // system
    IFB_ENG_INTERNAL void                         os_system_refresh_info             (os_context* os);

    // window
    IFB_ENG_INTERNAL void                         os_window_create_and_show          (os_context* os);


    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct os_context {
        os_system_info*   system_info;
        os_memory*        memory;
        os_file_table*    file_table;
        os_monitor_table* monitor_table;
        os_window*        window;
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
        os_window_handle     handle;
        os_window_position   position;
        os_window_size       size;
        os_window_viewport   viewport;
        os_window_event_list event_list;
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