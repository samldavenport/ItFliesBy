#pragma once

#include "ifb-engine-core-window.hpp"
#include "ifb-engine-core-monitor.hpp"
#include "ifb-engine-gui.hpp"
#include "ifb-engine-asset-config.hpp"
namespace ifb::eng {

    IFB_ENG_API bool
    core_startup(
        void) {

        // start managers 
        eng_mem_mngr_startup   ();
        eng_file_mngr_startup  ();
        eng_asset_mngr_startup ();

        // initialize platform
        core_monitor_table_init               ();
        core_window_init                      ();
        core_window_center_to_primary_monitor ();
        core_window_open_and_show             ();

        // initialize gui
        gui_init();

        return(true); 
    }

    IFB_ENG_API bool
    core_shutdown(
        void) {

        //////////////////////////
        // TODO(SAM):
        // - close all windows
        // - close all files
        // - sync and exit all threads
        // - release all memory
        //////////////////////////

        return(true);
    }

    IFB_ENG_API bool
    core_update(
        void) {

        core_window_process_events();

        return(true);
    }

    IFB_ENG_API bool
    core_render(
        void) {

        eng::gui_render();
        core_window_swap_buffers();

        return(true);
    }

    IFB_ENG_API bool
    core_should_quit(
        void) {

        bool core_should_quit = false;

        const core_window_update_t& window_update = core_window_get_update();

        core_should_quit |= (window_update.events.val & sld::os_window_event_e_quit);

        return(core_should_quit);
    }
};

