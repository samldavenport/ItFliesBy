#pragma once

#include "ifb-engine-gui.hpp"
#include "ifb-engine-file.hpp"
#include "ifb-engine-asset-config.hpp"
#include "ifb-engine-core-internal.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr cchar CSTR_WINDOW_TITLE         [] = "Asset Config"; 
    constexpr cchar CSTR_CONFIG_FILE_FILTER   [] = "XML Files\0*.xml\0";
    constexpr cchar CSTR_DIALOG_TITLE_NEW     [] = "New Asset Config";
    constexpr cchar CSTR_DIALOG_TITLE_SAVE_AS [] = "Save Asset Config As";
    constexpr cchar CSTR_DIALOG_TITLE_OPEN    [] = "Open Asset Config";

    //-------------------------------------------------------------------
    // GLOBALS
    //-------------------------------------------------------------------

    IFB_ENG_GLOBAL asset_config_context_t    _config_context;
    IFB_ENG_GLOBAL core_window_file_dialog_t _file_dialog;

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void gui_asset_config_settings (void);
    IFB_ENG_INTERNAL void gui_asset_config_menu_bar (void);
    IFB_ENG_INTERNAL void gui_asset_config_new      (void);
    IFB_ENG_INTERNAL void gui_asset_config_open     (void);
    IFB_ENG_INTERNAL void gui_asset_config_save     (void);
    IFB_ENG_INTERNAL void gui_asset_config_save_as  (void);

    //-------------------------------------------------------------------
    // METHODS
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
                if (ImGui::MenuItem("New",       NULL)) gui_asset_config_new     ();
                if (ImGui::MenuItem("Open...",   NULL)) gui_asset_config_open    ();
                if (ImGui::MenuItem("Save",      NULL)) gui_asset_config_save    ();
                if (ImGui::MenuItem("Save As..", NULL)) gui_asset_config_save_as ();
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
    }

    IFB_ENG_INTERNAL void
    gui_asset_config_new(
        void) {

        _file_dialog.filter        = CSTR_CONFIG_FILE_FILTER;
        _file_dialog.starting_path = NULL;
        _file_dialog.title         = CSTR_DIALOG_TITLE_NEW;

        eng::core_window_save_file_dialog(_file_dialog);
    }

    IFB_ENG_INTERNAL void
    gui_asset_config_open(
        void) {

        _file_dialog.filter        = CSTR_CONFIG_FILE_FILTER;
        _file_dialog.starting_path = NULL;
        _file_dialog.title         = CSTR_DIALOG_TITLE_OPEN;

        eng::core_window_open_file_dialog(_file_dialog);
    }

    IFB_ENG_INTERNAL void
    gui_asset_config_save(
        void) {

    }

    IFB_ENG_INTERNAL void
    gui_asset_config_save_as(
        void) {

        _file_dialog.filter        = CSTR_CONFIG_FILE_FILTER;
        _file_dialog.starting_path = NULL;
        _file_dialog.title         = CSTR_DIALOG_TITLE_SAVE_AS;

        eng::core_window_save_file_dialog(_file_dialog);
    }
};