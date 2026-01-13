#pragma once

#include "devconsole.hpp"
#include "devconsole-font.hpp"
#include "memory.hpp"

namespace ifb::eng {

    static devconsole* _console;

    IFB_ENG_INTERNAL devconsole*
    devconsole_init(
        void) {

        _console = singleton_alloc_struct<devconsole>();
        assert(_console);

        _console->flags = devconsole_flag_e_none;

        return(_console);
    }

    IFB_ENG_INTERNAL void
    devconsole_start_gui(
        void) {

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.Fonts->AddFontFromMemoryCompressedBase85TTF(
            DEVTOOLS_FONT_OPENSANS_COMPRESSED_BASE85, 16.0f
        );
    }

    IFB_ENG_INTERNAL bool
    devconsole_is_active(
        void) {

        assert(_console);

        const bool is_active = (_console->flags & devconsole_flag_e_active);
        return(is_active);
    }

    IFB_ENG_INTERNAL void
    devconsole_set_active(
        void) {

        assert(_console);
        _console->flags |= devconsole_flag_e_active;
    }
    
    IFB_ENG_INTERNAL void
    devconsole_set_inactive(
        void) {

        assert(_console);
        _console->flags &= ~devconsole_flag_e_active;
    }

    IFB_ENG_INTERNAL void
    devconsole_toggle(
        void) {

        assert(_console);
        _console->flags ^= devconsole_flag_e_active;
    }

    IFB_ENG_INTERNAL void
    devconsole_render(
        void) {

        assert(_console);

        const bool is_active = (_console->flags & devconsole_flag_e_active);
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