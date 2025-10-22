#pragma once

#include "ifb-engine-gui.hpp"

namespace ifb {

    IFB_ENG_FUNC void
    gui_imgui(
        void) {

        bool is_open_base_demo = gui_imgui_window_is_open(gui_e32_flag_imgui_base_demo);
        bool is_open_plot_demo = gui_imgui_window_is_open(gui_e32_flag_imgui_plot_demo);

        if (is_open_base_demo) {
            ImGui::ShowDemoWindow(&is_open_base_demo);
        }
        if (is_open_plot_demo) {
            //TODO
        }

        if (!is_open_base_demo) gui_imgui_window_close(gui_e32_flag_imgui_base_demo);
        if (!is_open_plot_demo) gui_imgui_window_close(gui_e32_flag_imgui_plot_demo);
    }
};