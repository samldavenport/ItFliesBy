#ifndef IFB_ENGINE_GUI_INTERNAL_HPP
#define IFB_ENGINE_GUI_INTERNAL_HPP

#include <imgui.h>
#include <imgui/L2DFileDialog.h>

#include "ifb-engine.hpp"
#include "ifb-engine-gui-widgets.hpp"
#include "ifb-engine-gui-menu-bar.hpp"


namespace ifb::eng {

    struct gui_t {
        gui_menu_bar_flags_t menu_bar_flags;
    } static _gui;

    IFB_ENG_FUNC void gui_init   (void);
    IFB_ENG_FUNC void gui_render (void);

};


#endif //IFB_ENGINE_GUI_INTERNAL_HPP