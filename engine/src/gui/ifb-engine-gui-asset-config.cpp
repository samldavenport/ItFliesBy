#pragma once

#include "ifb-engine-gui.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // INTERNAL CONSTANTS
    //-------------------------------------------------------------------

    constexpr cchar GUI_ASSET_CONFIG_CSTR_WINDOW[] = "Asset Config";

    struct gui_asset_config_settings_control_t {
        gui_widget_label_t      label;
        gui_widget_input_text_t input;
        gui_widget_button_t     button;
    };

    //-------------------------------------------------------------------
    // INTERNAL DECLARATIONS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void gui_asset_config_settings         (void);
    IFB_ENG_INTERNAL bool gui_asset_config_settings_control (gui_asset_config_settings_control_t& ctrl);
    IFB_ENG_INTERNAL void gui_asset_config_section_text     (void);

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

        gui_asset_config_settings();

        if (!is_open) {
            gui_asset_flag_clear         (gui_asset_flag_e_config);
            asset_config_context_destroy (_gui_asset_state.config_context);            
        }

        ImGui::End();
    }

    IFB_ENG_INTERNAL void
    gui_asset_config_settings(
        void) {
        
        static gui_asset_config_settings_control_t ctrl_config = {
            gui_widget_label_init      ("Config Path"),       // label
            gui_widget_input_text_init ("input-path-config"), // input
            gui_widget_button_init     ("Browse")             // button    
        };
        static gui_asset_config_settings_control_t ctrl_assets = {
            gui_widget_label_init      ("Assets Path"),       // label
            gui_widget_input_text_init ("input-path-assets"), // input
            gui_widget_button_init     ("Browse")             // button    
        };

        ImGui::SeparatorText("Config Settings");

        const bool begin_table = ImGui::BeginTable("config-settings", 3, ImGuiTableFlags_None);
        if (begin_table) {

            ImGui::TableSetupColumn("config-settings-table-column-label",  ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("config-settings-table-column-input",  ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("config-settings-table-column-browse", ImGuiTableColumnFlags_WidthStretch);

            const bool browse_config = gui_asset_config_settings_control(ctrl_config);
            const bool browse_assets = gui_asset_config_settings_control(ctrl_assets);

            ImGui::EndTable();
        }
    }

    IFB_ENG_INTERNAL bool
    gui_asset_config_settings_control(
        gui_asset_config_settings_control_t& ctrl) {

        constexpr u32 column_index_label  = 0;
        constexpr u32 column_index_input  = 1;
        constexpr u32 column_index_browse = 2;

        ImGui::TableNextRow();

        // label
        ImGui::TableSetColumnIndex(column_index_label);
        gui_widget_label_render(ctrl.label);
        
        // input
        ImGui::TableSetColumnIndex(column_index_input);
        gui_widget_input_text_render(ctrl.input);
        
        // button
        ImGui::TableSetColumnIndex(column_index_browse);
        const bool button_clicked = gui_widget_button_render(ctrl.button); 
        
        return(button_clicked);
    }

    IFB_ENG_INTERNAL void
    gui_asset_config_section_text(
        void) {

    }

};