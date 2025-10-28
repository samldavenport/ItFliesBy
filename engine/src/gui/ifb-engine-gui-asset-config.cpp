#pragma once

#include "ifb-engine-gui.hpp"
#include "ifb-engine-file.hpp"
#include "ifb-engine-asset-config.hpp"
#include "ifb-engine-core-internal.hpp"

#define CSTR_WINDOW_TITLE               "Asset Config"
#define CSTR_SETTINGS_CONFIG_LABEL_PATH "Config Path:"
#define CSTR_SETTINGS_ASSETS_LABEL_PATH "Assets Path:"
#define CSTR_SETTINGS_BROWSE_BUTTON     "Browse"
#define CSTR_SETTINGS_SEPARATOR         "Config Settings" 

namespace ifb::eng {

    constexpr cchar CSTR_CONFIG_FILE_FILTER[] = "XML Files\0*.xml\0";

    //-------------------------------------------------------------------
    // INTERNAL TYPES
    //-------------------------------------------------------------------

    struct gui_asset_config_settings_control_t {
        gui_widget_text_c32_t   label;
        gui_widget_input_text_t input;
        gui_widget_button_t     button;
    };

    //-------------------------------------------------------------------
    // INTERNAL GLOBALS
    //-------------------------------------------------------------------

    static asset_config_context_t _config_context;

    //-------------------------------------------------------------------
    // INTERNAL DECLARATIONS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void gui_asset_config_settings           (void);
    IFB_ENG_INTERNAL bool gui_asset_config_settings_control   (gui_asset_config_settings_control_t& ctrl);
    IFB_ENG_INTERNAL void gui_asset_config_browse_config_file (string_c256_t& file_path);
    IFB_ENG_INTERNAL void gui_asset_config_browse_assets_dir  (string_c256_t& dir_path);
    IFB_ENG_INTERNAL void gui_asset_config_section_text       (void);
    IFB_ENG_INTERNAL void gui_asset_config_menu_bar           (void);

    //-------------------------------------------------------------------
    // INTERNAL METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void
    gui_asset_render_config(
        void) {

        bool context_is_valid = asset_config_context_is_valid(_config_context);

        if (!gui_asset_flag_state(gui_asset_flag_e_config)) {

            if (context_is_valid) {
                asset_config_context_destroy(_config_context);
            }
            return;
        }

        if (!context_is_valid) {
            asset_config_context_create(_config_context);
            context_is_valid = asset_config_context_is_valid(_config_context);
            assert(context_is_valid);
        }

        bool is_open = true;
        const ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
        const bool             window_begin = ImGui::Begin(CSTR_WINDOW_TITLE, &is_open, window_flags);

        if (!window_begin) {
            ImGui::End();
            return;
        }

        gui_asset_config_menu_bar();

        if (!is_open) {
            gui_asset_flag_clear(gui_asset_flag_e_config);
            asset_config_context_destroy(_config_context);
        }

        ImGui::End();
    }

    IFB_ENG_INTERNAL void
    gui_asset_config_menu_bar(
        void) {

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                const bool file_new     = ImGui::MenuItem("New",       NULL);
                const bool file_open    = ImGui::MenuItem("Open...",   NULL);
                const bool file_save    = ImGui::MenuItem("Save",      NULL);
                const bool file_save_as = ImGui::MenuItem("Save As..", NULL);
                ImGui::EndMenu();

                if (file_new) {
                    eng_core_window_save_file_dialog(NULL, CSTR_CONFIG_FILE_FILTER);
                }


            }
            ImGui::EndMenuBar();
        }
    }

    IFB_ENG_INTERNAL void
    gui_asset_config_settings(
        void) {

        static gui_asset_config_settings_control_t ctrl_config = {
            gui_widget_text_c32_init   (CSTR_SETTINGS_CONFIG_LABEL_PATH), // label
            gui_widget_input_text_init (NULL),                            // input
            gui_widget_button_init     (CSTR_SETTINGS_BROWSE_BUTTON)      // button    
        };
        static gui_asset_config_settings_control_t ctrl_assets = {
            gui_widget_text_c32_init   (CSTR_SETTINGS_ASSETS_LABEL_PATH), // label
            gui_widget_input_text_init (NULL),                            // input
            gui_widget_button_init     (CSTR_SETTINGS_BROWSE_BUTTON)      // button    
        };
        static bool show_file_dialog_config = false;
        static bool show_file_dialog_assets = false;

        ImGui::SeparatorText(CSTR_SETTINGS_SEPARATOR);

        const bool begin_table = ImGui::BeginTable(GUI_WIDGET_CSTR_UNNAMED, 3, ImGuiTableFlags_None);
        if (begin_table) {

            ImGui::TableSetupColumn(GUI_WIDGET_CSTR_UNNAMED, ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn(GUI_WIDGET_CSTR_UNNAMED, ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn(GUI_WIDGET_CSTR_UNNAMED, ImGuiTableColumnFlags_WidthStretch);

            const bool browse_config = gui_asset_config_settings_control(ctrl_config);
            const bool browse_assets = gui_asset_config_settings_control(ctrl_assets);

            const cchar* config_selection = (browse_config) ? eng_core_window_open_file_dialog() : NULL;
            if (config_selection) {
                strncpy_s(
                    ctrl_config.input.buffer.chars,
                    GUI_WIDGET_SIZE_INPUT,
                    config_selection,
                    GUI_WIDGET_SIZE_INPUT
                );
            }

            const cchar* assets_selection = (browse_assets) ? eng_core_window_open_file_dialog() : NULL;
            if (assets_selection) {
                strncpy_s(
                    ctrl_assets.input.buffer.chars,
                    GUI_WIDGET_SIZE_INPUT,
                    assets_selection,
                    GUI_WIDGET_SIZE_INPUT
                );
            }


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
        gui_widget_text_c32_render(ctrl.label);
        
        // input
        ImGui::TableSetColumnIndex(column_index_input);
        gui_widget_input_text_render(ctrl.input);
        
        // button
        ImGui::TableSetColumnIndex(column_index_browse);
        const bool button_clicked = gui_widget_button_render(ctrl.button); 
        
        return(button_clicked);
    }

    IFB_ENG_INTERNAL void
    gui_asset_config_browse_config_file(
        string_c256_t& file_path) {

        
    }

    IFB_ENG_INTERNAL void
    gui_asset_config_browse_assets_dir(
        string_c256_t& dir_path) {

    }



    IFB_ENG_INTERNAL void
    gui_asset_config_section_text(
        void) {

    }

};