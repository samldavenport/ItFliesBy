#pragma once

#include "ifb-engine-gui.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // INTERNAL DECLARATIONS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void gui_menu_bar_imgui  (void);
    IFB_ENG_INTERNAL void gui_menu_bar_assets (void);

    //-------------------------------------------------------------------
    // INTERNAL METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void
    gui_menu_bar_render(void) {

        if (ImGui::BeginMenuBar()) {
            gui_menu_bar_imgui  ();
            gui_menu_bar_assets ();
            ImGui::EndMenuBar();
        }
    }

    IFB_ENG_INTERNAL void
    gui_menu_bar_imgui(
        void) {

        if (ImGui::BeginMenu(GUI_MENU_BAR_CSTR_MENU_IMGUI)) {

            bool state_base_demo = gui_imgui_flag_state(gui_imgui_flag_e_base_demo);
            bool state_plot_demo = gui_imgui_flag_state(gui_imgui_flag_e_plot_demo);
            gui_imgui_flag_reset_all();

            ImGui::MenuItem(GUI_MENU_BAR_CSTR_ITEM_IMGUI_BASE_DEMO, NULL, &state_base_demo);
            ImGui::MenuItem(GUI_MENU_BAR_CSTR_ITEM_IMGUI_PLOT_DEMO, NULL, &state_plot_demo);
            ImGui::EndMenu();
            
            if (state_base_demo) gui_imgui_flag_set(gui_imgui_flag_e_base_demo);
            if (state_plot_demo) gui_imgui_flag_set(gui_imgui_flag_e_plot_demo);
        }
    }

    IFB_ENG_INTERNAL void
    gui_menu_bar_assets(
        void) {
        
        if (ImGui::BeginMenu(GUI_MENU_BAR_CSTR_MENU_ASSETS)) {

            bool state_text     = gui_asset_flag_state(gui_asset_flag_e_open_text);
            bool state_image    = gui_asset_flag_state(gui_asset_flag_e_open_image);
            bool state_sound    = gui_asset_flag_state(gui_asset_flag_e_open_sound);
            bool state_font     = gui_asset_flag_state(gui_asset_flag_e_open_font);
            bool state_config   = gui_asset_flag_state(gui_asset_flag_e_config);
            bool state_database = gui_asset_flag_state(gui_asset_flag_e_database);
            gui_asset_flag_reset_all();

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

            if (state_text)     gui_asset_flag_set(gui_asset_flag_e_open_text);     
            if (state_image)    gui_asset_flag_set(gui_asset_flag_e_open_image);    
            if (state_sound)    gui_asset_flag_set(gui_asset_flag_e_open_sound);    
            if (state_font)     gui_asset_flag_set(gui_asset_flag_e_open_font);     
            if (state_config)   gui_asset_flag_set(gui_asset_flag_e_config);   
            if (state_database) gui_asset_flag_set(gui_asset_flag_e_database); 
        }
    }
};