#pragma once

#include <sld-os.hpp>
#include <sld-cstr.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-memory-internal.hpp"

namespace ifb {

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr cchar ENG_CORE_WINDOW_TITLE[]                     = "It Flies By";
    constexpr u32   ENG_CORE_WINDOW_DEFAULT_WIDTH               = 1024;
    constexpr u32   ENG_CORE_WINDOW_DEFAULT_HEIGHT              = 768;
    constexpr u32   ENG_CORE_WINDOW_DEFAULT_SCREEN_X            = 0;
    constexpr u32   ENG_CORE_WINDOW_DEFAULT_SCREEN_Y            = 0;
    constexpr u32   ENG_CORE_WINDOW_INPUT_QUEUE_COUNT           = 8;
    constexpr u32   ENG_CORE_WINDOW_INPUT_QUEUE_KEYBOARD_SIZE   = sizeof(sld::os_input_keycode_t) * ENG_CORE_WINDOW_INPUT_QUEUE_COUNT;
    constexpr u32   ENG_CORE_WINDOW_INPUT_QUEUE_KEYBOARD_STRIDE = sizeof(sld::os_input_keycode_t);
    constexpr u32   ENG_CORE_MONITOR_COUNT_MAX                  = 16;
    constexpr u32   ENG_CORE_MONITOR_NAME_LENGTH                = sld::OS_MONITOR_NAME_WIDTH;
    constexpr u32   ENG_CORE_MONITOR_NAME_BUFFER_SIZE           = (ENG_CORE_MONITOR_COUNT_MAX * sld::OS_MONITOR_NAME_WIDTH); 

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using  eng_core_monitor_handle_t = sld::os_monitor_handle_t;
    using  eng_core_monitor_pos_t    = sld::dims_u32_pos_t;
    using  eng_core_monitor_size_t   = sld::dims_u32_size_t;
    struct eng_core_monitor_name_t;

    using eng_core_window_handle_t   = sld::os_window_handle_t;
    using eng_core_window_update_t   = sld::os_window_update_t;
    using eng_core_window_error_t    = sld::os_window_error_t;
    using eng_core_window_pos_t      = sld::dims_u32_pos_t;
    using eng_core_window_size_t     = sld::dims_u32_size_t;

    using eng_core_input_keyboard_t  = sld::input_keyboard_t;
    
    struct eng_core_window_t;
    struct eng_core_monitor_table_t;

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct eng_core_window_t {
        eng_core_window_error_t  last_error;
        eng_core_window_handle_t handle;
        eng_core_window_pos_t    position;          
        eng_core_window_size_t   size;
        eng_core_window_update_t update;
    };

    struct eng_core_monitor_table_t {
        eng_core_monitor_handle_t monitor_primary;         
        eng_core_monitor_handle_t monitor_active;         
        eng_core_monitor_size_t   monitor_virtual_size;
        u64                       monitor_count;
        struct {
            eng_core_monitor_pos_t*    position;
            eng_core_monitor_size_t*   size;
            eng_core_monitor_name_t*   name;
            eng_core_monitor_handle_t* handle;
        } array;
    };

    struct eng_core_monitor_name_t {
        cchar cstr[ENG_CORE_MONITOR_NAME_LENGTH];
    };
    struct eng_core_monitor_info_t {
        eng_core_monitor_handle_t os_handle;
        eng_core_monitor_pos_t    pos;
        eng_core_monitor_size_t   size;
        eng_core_monitor_name_t   name;
    };

    //-------------------------------------------------------------------
    // SINGLETONS
    //-------------------------------------------------------------------

    static eng_core_window_t         _eng_core_window;
    static eng_core_input_keyboard_t _eng_core_input_keyboard;
    static eng_core_monitor_table_t  _eng_core_monitor_table;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void eng_core_window_init                      (void);
    IFB_ENG_INTERNAL void eng_core_window_open_and_show             (void);
    IFB_ENG_INTERNAL void eng_core_window_process_events            (void);
    IFB_ENG_INTERNAL void eng_core_window_swap_buffers              (void);
    IFB_ENG_INTERNAL void eng_core_window_center_to_monitor         (const eng_core_monitor_handle_t monitor);
    IFB_ENG_INTERNAL void eng_core_window_center_to_primary_monitor (void);

    IFB_ENG_INTERNAL bool eng_core_monitor_table_validate           (void);
    IFB_ENG_INTERNAL void eng_core_monitor_table_init               (void);
    IFB_ENG_INTERNAL void eng_core_monitor_table_refresh            (void);
    IFB_ENG_INTERNAL u32  eng_core_monitor_table_search             (const eng_core_monitor_handle_t monitor);
    IFB_ENG_INTERNAL void eng_core_monitor_get_size                 (const eng_core_monitor_handle_t monitor, eng_core_monitor_size_t& size);
    IFB_ENG_INTERNAL void eng_core_monitor_get_position             (const eng_core_monitor_handle_t monitor, eng_core_monitor_pos_t&  pos);
    IFB_ENG_INTERNAL void eng_core_monitor_get_name                 (const eng_core_monitor_handle_t monitor, eng_core_monitor_name_t& name);
    IFB_ENG_INTERNAL void eng_core_monitor_get_info                 (const eng_core_monitor_handle_t monitor, eng_core_monitor_info_t& info);

};
