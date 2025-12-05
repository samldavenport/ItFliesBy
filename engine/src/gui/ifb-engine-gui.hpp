#ifndef IFB_ENGINE_GUI_INTERNAL_HPP
#define IFB_ENGINE_GUI_INTERNAL_HPP

#include <imgui.h>
#include "ifb-engine.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void gui_init   (void);
    IFB_ENG_INTERNAL void gui_render (void);

};


#endif //IFB_ENGINE_GUI_INTERNAL_HPP