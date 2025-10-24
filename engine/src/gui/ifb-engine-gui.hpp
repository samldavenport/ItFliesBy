#ifndef IFB_ENGINE_GUI_INTERNAL_HPP
#define IFB_ENGINE_GUI_INTERNAL_HPP

#include <imgui.h>
#include <imgui/L2DFileDialog.h>

#include "ifb-engine.hpp"
#include "ifb-engine-gui-widgets.hpp"
#include "ifb-engine-gui-menu-bar.hpp"
#include "ifb-engine-gui-imgui.hpp"
#include "ifb-engine-gui-asset.hpp"
#include "ifb-engine-gui-utils.hpp"


namespace ifb::eng {

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void gui_init   (void);
    IFB_ENG_INTERNAL void gui_render (void);

};


#endif //IFB_ENGINE_GUI_INTERNAL_HPP