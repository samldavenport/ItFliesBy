#ifndef IFB_ENGINE_CORE_WINDOW_HPP
#define IFB_ENGINE_CORE_WINDOW_HPP

#include <sld-os.hpp>
#include <sld-cstr.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-memory-internal.hpp"
#include "ifb-engine-string.hpp"
#include "ifb-engine-core-monitor.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr cchar CORE_WINDOW_TITLE[]                           = "It Flies By";
    constexpr u32   CORE_WINDOW_DEFAULT_WIDTH                     = 1024;
    constexpr u32   CORE_WINDOW_DEFAULT_HEIGHT                    = 768;
    constexpr u32   CORE_WINDOW_DEFAULT_SCREEN_X                  = 0;
    constexpr u32   CORE_WINDOW_DEFAULT_SCREEN_Y                  = 0;
    constexpr u32   CORE_WINDOW_INPUT_QUEUE_COUNT                 = 8;
    constexpr u32   CORE_WINDOW_FILE_DIALOG_SELECTION_BUFFER_SIZE = sld::size_kilobytes(64);

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------

    struct core_window_t;
    struct core_window_file_dialog_t;
    struct core_window_file_dialog_selection_t;

    using  core_window_handle_t = sld::os_window_handle_t;
    using  core_window_update_t = sld::os_window_update_t;
    using  core_window_error_t  = sld::os_window_error_t;
    using  core_window_pos_t    = sld::dims_u32_pos_t;
    using  core_window_size_t   = sld::dims_u32_size_t;

    IFB_ENG_INTERNAL void                        core_window_init                      (void);
    IFB_ENG_INTERNAL void                        core_window_open_and_show             (void);
    IFB_ENG_INTERNAL void                        core_window_process_events            (void);
    IFB_ENG_INTERNAL void                        core_window_swap_buffers              (void);
    IFB_ENG_INTERNAL void                        core_window_center_to_monitor         (const core_monitor_index_t monitor_index);
    IFB_ENG_INTERNAL void                        core_window_center_to_primary_monitor (void);
    IFB_ENG_INTERNAL const cchar*                core_window_open_file_dialog          (const core_window_file_dialog_t& file_dialog);
    IFB_ENG_INTERNAL const cchar*                core_window_save_file_dialog          (const core_window_file_dialog_t& file_dialog);
    IFB_ENG_INTERNAL const core_window_update_t& core_window_get_update                (void);
    IFB_ENG_INTERNAL bool                        core_window_quit_received             (void);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct core_window_t {
        core_window_error_t  last_error;
        core_window_handle_t handle;
        core_window_pos_t    position;          
        core_window_size_t   size;
        core_window_update_t update;
    };
    
    struct core_window_file_dialog_t {
        const cchar* title;
        const cchar* starting_path;
        const cchar* filter;
    };

    struct core_window_file_dialog_selection_t {
        cchar buffer[CORE_WINDOW_FILE_DIALOG_SELECTION_BUFFER_SIZE];
    };
};

#endif //IFB_ENGINE_CORE_WINDOW_HPP