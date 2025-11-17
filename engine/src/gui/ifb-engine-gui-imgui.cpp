#pragma once

#include "ifb-engine-gui.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    gui_imgui_render(
        void) {

        static bool window_open = false;

        if (gui_imgui_flag_state(gui_imgui_flag_e_base_demo)) {
            window_open = true;
            ImGui::ShowDemoWindow(&window_open);
            if (!window_open) gui_imgui_flag_clear(gui_imgui_flag_e_base_demo);
        }

        if (gui_imgui_flag_state(gui_imgui_flag_e_plot_demo)) {
            //TODO
        }

    }
};