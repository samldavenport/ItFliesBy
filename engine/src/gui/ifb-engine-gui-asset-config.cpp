#pragma once

#include "ifb-engine-gui.hpp"
#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    constexpr cchar CSTR_HEADER_LABEL_TEXT                     [] = "Text";
    constexpr cchar CSTR_HEADER_LABEL_IMAGE                    [] = "Images";
    constexpr cchar CSTR_HEADER_LABEL_SOUND                    [] = "Sounds";
    constexpr cchar CSTR_HEADER_LABEL_FONT                     [] = "Fonts";
    constexpr cchar CSTR_PATH_INPUT_CONFIG_FILE_LABEL_TEXT     [] = "Config File:";
    constexpr cchar CSTR_PATH_INPUT_ASSET_DIR_INPUT_LABEL_TEXT [] = "Asset Directory:";
    constexpr cchar CSTR_INPUT_BUTTON_SUBMIT_FILE              [] = "Submit File";
    constexpr cchar CSTR_INPUT_BUTTON_SUBMIT_DIR               [] = "Submit Dir";

    struct gui_asset_config_t {
        gui_input_cstr_t asset_folder;
        gui_input_cstr_t asset_config;
    };

    IFB_ENG_INTERNAL void
    gui_asset_config(
        void) {

        constexpr cchar window_name_cstr[] = "Asset Config";
        bool is_open = gui_assets_window_is_open(gui_e32_flag_assets_config);

        if (is_open) {
            if (ImGui::Begin(window_name_cstr, &is_open)) {

                gui_asset_config_path_input ();
                gui_asset_config_text       ();
                gui_asset_config_image      ();
                gui_asset_config_sound      ();
                gui_asset_config_font       ();
            }
            ImGui::End();
        }

        if (!is_open) {
            gui_assets_window_close(gui_e32_flag_assets_config);
        }
    }

    IFB_ENG_INTERNAL void
    gui_asset_config_path_input(
        void) {

        constexpr u32 input_size       = sizeof(gui_input_cstr_t); 
        constexpr u32 path_input_file  = 0; 
        constexpr u32 path_input_dir   = 1; 
        constexpr u32 path_input_count = 2; 

        static gui_text_input_t path_text_input_array [path_input_count] = {
            gui_text_input_init(CSTR_INPUT_BUTTON_SUBMIT_FILE, CSTR_PATH_INPUT_CONFIG_FILE_LABEL_TEXT),    // path_input_file
            gui_text_input_init(CSTR_INPUT_BUTTON_SUBMIT_DIR,  CSTR_PATH_INPUT_ASSET_DIR_INPUT_LABEL_TEXT) // path_input_asset_directory
        };
        gui_text_input(path_text_input_array, path_input_count);

        static bool      is_dialog_open_file     = false;
        static bool      is_dialog_open_dir      = false;
        const  bool      is_clicked_button_file  = path_text_input_array[path_input_file].button_clicked; 
        const  bool      is_clicked_button_dir   = path_text_input_array[path_input_dir].button_clicked; 
        const  bool      should_open_dialog_file = (is_dialog_open_file || is_clicked_button_file);
        const  bool      should_open_dialog_dir  = (is_dialog_open_dir  || is_clicked_button_dir);

        if (should_open_dialog_file) {

            is_dialog_open_file               = true;            
            FileDialog::file_dialog_open      = is_dialog_open_file;
            FileDialog::file_dialog_open_type = FileDialog::FileDialogType::OpenFile;
            cchar* input_buffer               = path_text_input_array[path_input_file].input_string.buffer; 

            if (FileDialog::file_dialog_open) {
                FileDialog::ShowFileDialog(
                    &FileDialog::file_dialog_open,
                    input_buffer,
                    input_size
                );
            }

            is_dialog_open_file = FileDialog::file_dialog_open;
        }

        if (should_open_dialog_dir) {

            is_dialog_open_dir                = true;
            FileDialog::file_dialog_open      = is_dialog_open_dir;
            FileDialog::file_dialog_open_type = FileDialog::FileDialogType::SelectFolder;
            cchar*      input_buffer          = path_text_input_array[path_input_dir].input_string.buffer; 

            if (FileDialog::file_dialog_open) {
                FileDialog::ShowFileDialog(
                    &FileDialog::file_dialog_open,
                    input_buffer,
                    input_size
                );
            }

            is_dialog_open_dir = FileDialog::file_dialog_open;
        }
    }

    IFB_ENG_INTERNAL void
    gui_asset_config_text(
        void) {

        const ImGuiTreeNodeFlags header_flags = ImGuiTreeNodeFlags_None;
        if (ImGui::CollapsingHeader(CSTR_HEADER_LABEL_TEXT)) {
            
        }
    }

    IFB_ENG_INTERNAL void
    gui_asset_config_image(
        void) {

        const ImGuiTreeNodeFlags header_flags = ImGuiTreeNodeFlags_None;
        if (ImGui::CollapsingHeader(CSTR_HEADER_LABEL_IMAGE)) {

        }
    }

    IFB_ENG_INTERNAL void
    gui_asset_config_sound(
        void) {

        const ImGuiTreeNodeFlags header_flags = ImGuiTreeNodeFlags_None;
        if (ImGui::CollapsingHeader(CSTR_HEADER_LABEL_SOUND)) {

        }
    }

    IFB_ENG_INTERNAL void
    gui_asset_config_font(
        void) {

        const ImGuiTreeNodeFlags header_flags = ImGuiTreeNodeFlags_None;
        if (ImGui::CollapsingHeader(CSTR_HEADER_LABEL_FONT)) {

        }
    }

};