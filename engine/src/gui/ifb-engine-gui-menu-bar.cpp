#pragma once

#include "ifb-engine-gui.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    gui_menu_bar_render(void) {

        if (ImGui::BeginMenuBar()) {
            gui_menu_bar_imgui  ();
            gui_menu_bar_assets ();
        }
    }

    IFB_ENG_INTERNAL void
    gui_menu_bar_imgui(
        void) {

        if (ImGui::BeginMenu(GUI_MENU_BAR_CSTR_MENU_IMGUI)) {
            
            bool state_base_demo = (_gui.menu_bar_flags.imgui.val & gui_menu_bar_imgui_item_flag_base_demo);
            bool state_plot_demo = (_gui.menu_bar_flags.imgui.val & gui_menu_bar_imgui_item_flag_plot_demo);
            _gui.menu_bar_flags.imgui.val  = gui_menu_bar_imgui_item_flag_none; 

            ImGui::MenuItem(GUI_MENU_BAR_CSTR_ITEM_IMGUI_BASE_DEMO, NULL, &state_base_demo);
            ImGui::MenuItem(GUI_MENU_BAR_CSTR_ITEM_IMGUI_PLOT_DEMO, NULL, &state_plot_demo);
            ImGui::EndMenu();
            
            if (state_base_demo) (_gui.menu_bar_flags.imgui.val |= gui_menu_bar_imgui_item_flag_base_demo); 
            if (state_plot_demo) (_gui.menu_bar_flags.imgui.val |= gui_menu_bar_imgui_item_flag_plot_demo); 
        }
    }

    IFB_ENG_INTERNAL void
    gui_menu_bar_assets(
        void) {
        
        if (ImGui::BeginMenu(GUI_MENU_BAR_CSTR_MENU_ASSETS)) {

            bool state_text     = _gui.menu_bar_flags.assets.val & gui_menu_bar_asset_item_flag_open_text;
            bool state_image    = _gui.menu_bar_flags.assets.val & gui_menu_bar_asset_item_flag_open_image;
            bool state_sound    = _gui.menu_bar_flags.assets.val & gui_menu_bar_asset_item_flag_open_sound;
            bool state_font     = _gui.menu_bar_flags.assets.val & gui_menu_bar_asset_item_flag_open_font;
            bool state_config   = _gui.menu_bar_flags.assets.val & gui_menu_bar_asset_item_flag_config;
            bool state_database = _gui.menu_bar_flags.assets.val & gui_menu_bar_asset_item_flag_database;
            _gui.menu_bar_flags.assets.val = gui_menu_bar_asset_item_flag_none;

            if (ImGui::BeginMenu(GUI_MENU_BAR_CSTR_ITEM_ASSETS_OPEN_FILE)) {

                ImGui::MenuItem(GUI_MENU_BAR_CSTR_ITEM_ASSETS_TEXT,  NULL, &state_text);
                ImGui::MenuItem(GUI_MENU_BAR_CSTR_ITEM_ASSETS_IMAGE, NULL, &state_image);
                ImGui::MenuItem(GUI_MENU_BAR_CSTR_ITEM_ASSETS_SOUND, NULL, &state_sound);
                ImGui::MenuItem(GUI_MENU_BAR_CSTR_ITEM_ASSETS_FONT,  NULL, &state_font);
                ImGui::EndMenu();
            }

            ImGui::MenuItem(GUI_MENU_BAR_CSTR_ITEM_ASSETS_CONFIG,   NULL, &state_config);
            ImGui::MenuItem(GUI_MENU_BAR_CSTR_ITEM_ASSETS_DATABASE, NULL, &state_database);
            ImGui::EndMenu();

            if (state_text)     _gui.menu_bar_flags.assets.val |= gui_menu_bar_asset_item_flag_open_text;
            if (state_image)    _gui.menu_bar_flags.assets.val |= gui_menu_bar_asset_item_flag_open_image;
            if (state_sound)    _gui.menu_bar_flags.assets.val |= gui_menu_bar_asset_item_flag_open_sound;
            if (state_font)     _gui.menu_bar_flags.assets.val |= gui_menu_bar_asset_item_flag_open_font;
            if (state_config)   _gui.menu_bar_flags.assets.val |= gui_menu_bar_asset_item_flag_config;
            if (state_database) _gui.menu_bar_flags.assets.val |= gui_menu_bar_asset_item_flag_database;
        }
        ImGui::EndMenuBar();
    }
};