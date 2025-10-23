#pragma once

#include "ifb-engine-gui.hpp"
#include "ifb-engine-font-opensans.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    gui_init(
        void) {

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.Fonts->AddFontFromMemoryCompressedBase85TTF(
            ENG_OPENSANS_COMPRESSED_BASE85, 16.0f
        );
    }

    IFB_ENG_INTERNAL void
    gui_render(
        void) {

        constexpr ImGuiWindowFlags main_window_flags        = ImGuiWindowFlags_MenuBar;
        constexpr cchar            main_window_name_cstr [] = "IFB Dev Console";

        ImGui::EndDisabled();

        cchar buf[256];
        FileDialog::ShowFileDialog(
            buf,
            256, // buffer_size,
            FileDialog::FileDialogType::OpenFile
        );
        if (FileDialog::file_dialog_open) {
            ImGui::BeginDisabled();
        }

        const bool begin_main_window = ImGui::Begin(
            main_window_name_cstr,
            NULL,
            main_window_flags);

        if (!begin_main_window) {
            ImGui::End();
            return;
        }
        


        gui_menu_bar_render();
        gui_imgui_render();
        gui_asset_render_config();
        
        ImGui::End();
    }

};