#ifndef IFB_ENGINE_GUI_MENU_BAR_HPP
#define IFB_ENGINE_GUI_MENU_BAR_HPP

#include "ifb-engine.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr cchar GUI_MENU_BAR_CSTR_MENU_IMGUI            [] = "ImGui";
    constexpr cchar GUI_MENU_BAR_CSTR_MENU_ASSETS           [] = "Assets";

    constexpr cchar GUI_MENU_BAR_CSTR_ITEM_IMGUI_BASE_DEMO  [] = "ImGui Base Demo";
    constexpr cchar GUI_MENU_BAR_CSTR_ITEM_IMGUI_PLOT_DEMO  [] = "ImGui Plot Demo";

    constexpr cchar GUI_MENU_BAR_CSTR_ITEM_ASSETS_OPEN_FILE [] = "Open File";                
    constexpr cchar GUI_MENU_BAR_CSTR_ITEM_ASSETS_CONFIG    [] = "Config";
    constexpr cchar GUI_MENU_BAR_CSTR_ITEM_ASSETS_DATABASE  [] = "Database";
    constexpr cchar GUI_MENU_BAR_CSTR_ITEM_ASSETS_TEXT      [] = "Text";
    constexpr cchar GUI_MENU_BAR_CSTR_ITEM_ASSETS_IMAGE     [] = "Image";
    constexpr cchar GUI_MENU_BAR_CSTR_ITEM_ASSETS_SOUND     [] = "sound";
    constexpr cchar GUI_MENU_BAR_CSTR_ITEM_ASSETS_FONT      [] = "font";

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void gui_menu_bar_render (void);    
};

#endif //IFB_ENGINE_GUI_MENU_BAR_HPP