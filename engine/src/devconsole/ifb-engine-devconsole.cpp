#pragma once

#include "ifb-engine-devconsole.hpp"
#include "ifb-engine-devconsole-font.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    devconsole_init(
        devconsole* devconsole) {

        assert(devconsole);

        devconsole->flags = devconsole_flag_e_none;

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.Fonts->AddFontFromMemoryCompressedBase85TTF(
            DEVTOOLS_FONT_OPENSANS_COMPRESSED_BASE85, 16.0f
        );
    }

    IFB_ENG_INTERNAL bool
    devconsole_is_active(
        devconsole* devconsole) {

        assert(devconsole);

        const bool is_active = (devconsole->flags & devconsole_flag_e_active);
        return(is_active);
    }

    IFB_ENG_INTERNAL void
    devconsole_set_active(devconsole* devconsole) {

        assert(devconsole);
        devconsole->flags |= devconsole_flag_e_active;
    }
    
    IFB_ENG_INTERNAL void
    devconsole_set_inactive(
        devconsole* devconsole) {

        assert(devconsole);
        devconsole->flags &= ~devconsole_flag_e_active;
    }

    IFB_ENG_INTERNAL void
    devconsole_toggle(
        devconsole* dt) {

        assert(dt);
        dt->flags ^= devconsole_flag_e_active;
    }

    IFB_ENG_INTERNAL void
    devconsole_render(
        devconsole* devconsole) {

        assert(devconsole);

        const bool is_active = (devconsole->flags & devconsole_flag_e_active);
        if (!is_active) return;

        constexpr ImGuiWindowFlags main_window_flags        = ImGuiWindowFlags_MenuBar;
        constexpr cchar            main_window_name_cstr [] = "IFB Dev Console";

        const bool begin_main_window = ImGui::Begin( 
            main_window_name_cstr,
            NULL,
            main_window_flags);

        if (!begin_main_window) {
            ImGui::End();
            return;
        }
        
        ImGui::End();
    }

}; 