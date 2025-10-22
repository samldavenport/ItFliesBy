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
    constexpr cchar GUI_MENU_BAR_CSTR_ITEM_ASSETS_FONT     [] = "font";

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum gui_menu_bar_imgui_item_flag : u32 {
        gui_menu_bar_imgui_item_flag_none      = 0,
        gui_menu_bar_imgui_item_flag_base_demo = sld::bit_value(0),
        gui_menu_bar_imgui_item_flag_plot_demo = sld::bit_value(1)
    };

    enum gui_menu_bar_asset_item_flag : u32 {
        gui_menu_bar_asset_item_flag_none       = 0,
        gui_menu_bar_asset_item_flag_open_text  = sld::bit_value(1),
        gui_menu_bar_asset_item_flag_open_image = sld::bit_value(2),
        gui_menu_bar_asset_item_flag_open_sound = sld::bit_value(3),
        gui_menu_bar_asset_item_flag_open_font  = sld::bit_value(4),
        gui_menu_bar_asset_item_flag_config     = sld::bit_value(5),
        gui_menu_bar_asset_item_flag_database   = sld::bit_value(6)
    };

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------

    struct gui_menu_bar_t;
    using  gui_menu_bar_asset_item_flags = u32_t;
    using  gui_menu_bar_imgui_item_flags = u32_t;     

    IFB_ENG_INTERNAL        void gui_menu_bar_render            (void);
    IFB_ENG_INTERNAL        void gui_menu_bar_imgui             (void);
    IFB_ENG_INTERNAL        void gui_menu_bar_assets            (void);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct gui_menu_bar_flags_t {
        gui_menu_bar_asset_item_flags imgui;
        gui_menu_bar_imgui_item_flags assets;
    };
};

#endif //IFB_ENGINE_GUI_MENU_BAR_HPP