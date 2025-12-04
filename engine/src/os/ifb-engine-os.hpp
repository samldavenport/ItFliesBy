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

    constexpr u32 OS_FILE_MAX_COUNT          = IFB_ENG_CONFIG_OS_FILE_MAX_COUNT;
    constexpr u32 OS_FILE_INVALID            = 0xFFFFFFFF; 
    constexpr u32 OS_MONITOR_MAX_COUNT       = IFB_ENG_CONFIG_OS_MONITOR_MAX_COUNT;
    constexpr u32 OS_MONITOR_INVALID         = 0xFFFFFFFF; 
    constexpr u32 OS_WINDOW_EVENT_CAPACITY   = IFB_ENG_CONFIG_OS_WINDOW_EVENT_CAPACITY;
    constexpr u32 OS_WINDOW_KEYCODE_CAPACITY = IFB_ENG_CONFIG_OS_WINDOW_KEYCODE_CAPACITY;

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct os_context;
    struct os_memory;
    struct os_window;
    struct os_window_keycode_list;
    struct os_monitor_table;
    struct os_file_table;
    struct os_system_info;

    using os_file                = u32;
    using os_monitor             = u32;
    using os_window_flags        = u32;
    using os_window_mouse_button = u32;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    // context
    IFB_ENG_INTERNAL os_context* os_context_alloc               (stack& stack);
    IFB_ENG_INTERNAL void        os_context_init                (os_context* os);
    IFB_ENG_INTERNAL void        os_context_refresh_system_info (os_context* os);
    IFB_ENG_INTERNAL bool        os_context_frame_start         (os_context* os);
    IFB_ENG_INTERNAL bool        os_context_frame_render        (os_context* os);
    IFB_ENG_INTERNAL void        os_context_destroy             (os_context* os);

    // memory
    IFB_ENG_INTERNAL void        os_memory_reserve         (os_context* os);
    IFB_ENG_INTERNAL void        os_memory_release         (os_context* os);
    IFB_ENG_INTERNAL void*       os_memory_commit          (os_context* os, const u64   start, const u64 size);
    IFB_ENG_INTERNAL void        os_memory_decommit        (os_context* os, void* start, const u64 size);
    IFB_ENG_INTERNAL bool        os_memory_is_page_aligned (os_context* os, const u64   start);
    IFB_ENG_INTERNAL void        os_memory_check_usage     (os_context* os);

    // monitors
    IFB_ENG_INTERNAL void                         os_monitor_refresh_table  (os_context* os);
    IFB_ENG_INTERNAL const os_monitor_handle&     os_monitor_get_handle     (const os_context* os, const os_monitor monitor);
    IFB_ENG_INTERNAL const os_monitor_dimensions& os_monitor_get_dimensions (const os_context* os, const os_monitor monitor);
    IFB_ENG_INTERNAL const os_monitor_name&       os_monitor_get_name       (const os_context* os, const os_monitor monitor);

    // system
    IFB_ENG_INTERNAL void os_system_refresh_info    (os_context* os);

    // window
    IFB_ENG_INTERNAL void os_window_create_and_show                (os_context* os);
    IFB_ENG_INTERNAL void os_window_start_frame_and_process_events (os_context* os);
    IFB_ENG_INTERNAL void os_window_render_frame                   (os_context* os);

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

    struct os_window_input {
        struct {
            os_window_mouse_position position;
            os_window_mouse_button   button;
        } mouse;
        struct {
            os_window_keycode* array_down;
            os_window_keycode* array_up;
            u32                count_down;
            u32                count_up;
        } keycodes;
    };

    struct os_window {
        os_window_handle     handle;
        os_window_position   position;
        os_window_size       size;
        os_window_viewport   viewport;
        os_window_event_list event_list;
        os_window_flags      flags;
        os_window_input      input;
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
    
    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum os_window_flag_e {
        os_window_flag_e_none                       = 0,
        os_window_flag_e_visible                    = bit_value(0),
        os_window_flag_e_quit                       = bit_value(1),
        os_window_flag_e_frame_started              = bit_value(2),
        os_window_flag_e_viewport_changed           = bit_value(3),
        os_window_flag_e_keydown                    = bit_value(4),
        os_window_flag_e_keyup                      = bit_value(5),
        os_window_flag_e_mouse_button_clicked       = bit_value(6),
        os_window_flag_e_mouse_position_changed     = bit_value(7),
    };
    enum os_window_mouse_button_e {
        os_window_mouse_button_e_none               = 0,
        os_window_mouse_button_e_left_up            = 1,
        os_window_mouse_button_e_left_down          = 2,
        os_window_mouse_button_e_left_double_click  = 3,
        os_window_mouse_button_e_right_up           = 4,
        os_window_mouse_button_e_right_down         = 5,
        os_window_mouse_button_e_right_double_click = 6
    };
};

#endif //IFB_ENGINE_PLATFORM_MANAGER_HPP