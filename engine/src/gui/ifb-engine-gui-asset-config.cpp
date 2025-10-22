#pragma once

#include "ifb-engine-gui.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // INTERNAL CONSTANTS
    //-------------------------------------------------------------------

    constexpr cchar GUI_ASSET_CONFIG_CSTR_WINDOW[] = "Asset Config";

    //-------------------------------------------------------------------
    // INTERNAL DECLARATIONS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void gui_asset_render_config (bool* is_open);

    //-------------------------------------------------------------------
    // INTERNAL METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void
    gui_asset_render_config(
        void) {

        if (!gui_asset_flag_state(gui_asset_flag_e_config)) {
            return;
        }
        bool       is_open        = true;
        const bool should_destroy = !is_open &&  asset_config_context_is_valid(_gui_asset_state.config_context);
        const bool should_create  =  is_open && !asset_config_context_is_valid(_gui_asset_state.config_context);
        const bool window_begin   = ImGui::Begin(GUI_ASSET_CONFIG_CSTR_WINDOW, &is_open);
        
        assert(!(should_destroy && should_create));


        if (should_destroy) asset_config_context_destroy (_gui_asset_state.config_context);
        if (should_create)  asset_config_context_create  (_gui_asset_state.config_context);

        if (!window_begin) {
            ImGui::End();
            return;
        }

        if (!is_open) {
            gui_asset_flag_clear         (gui_asset_flag_e_config);
            asset_config_context_destroy (_gui_asset_state.config_context);            
        }

        ImGui::End();
    }
};