#pragma once

#include "ifb-engine-core-internal.hpp"
#include "ifb-engine-gui-internal.hpp"
#include "ifb-engine-asset-config.hpp"
namespace ifb {

    IFB_ENG_API bool
    eng_core_startup(
        void) {

        // start managers 
        eng_mem_mngr_startup   ();
        eng_file_mngr_startup  ();
        eng_asset_mngr_startup ();


        // initialize xml
        sld::xml_init();

        auto config = eng::asset_config_context_create();
        eng::asset_config_context_destroy(config);
        auto node = eng::asset_config_context_add_text_node(config, "name", "path");


        // initialize platform
        eng_core_monitor_table_init               ();
        eng_core_window_init                      ();
        eng_core_window_center_to_primary_monitor ();
        eng_core_window_open_and_show             ();

        // initialize gui
        eng_gui_init();

        return(true); 
    }

    IFB_ENG_API bool
    eng_core_shutdown(
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
    eng_core_update(
        void) {

        eng_core_window_process_events();

        return(true);
    }

    IFB_ENG_API bool
    eng_core_render(
        void) {

        eng_gui_render();
        eng_core_window_swap_buffers();

        return(true);
    }

    IFB_ENG_API bool
    eng_core_should_quit(
        void) {

        bool eng_core_should_quit = false;

        eng_core_should_quit |= (_eng_core_window.update.events.val & sld::os_window_event_e_quit);

        return(eng_core_should_quit);
    }
};

