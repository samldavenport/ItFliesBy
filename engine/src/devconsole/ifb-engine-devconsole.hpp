#ifndef IFB_ENGINE_GUI_INTERNAL_HPP
#define IFB_ENGINE_GUI_INTERNAL_HPP

#include <imgui.h>
#include <sld-stack.hpp>
#include "ifb-engine.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using devconsole_flags = u32;

    struct devconsole;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL devconsole* devconsole_alloc        (stack& stack);
    IFB_ENG_INTERNAL void        devconsole_init         (devconsole* dt);
    IFB_ENG_INTERNAL bool        devconsole_is_active    (devconsole* dt);
    IFB_ENG_INTERNAL void        devconsole_set_active   (devconsole* dt);
    IFB_ENG_INTERNAL void        devconsole_set_inactive (devconsole* dt);
    IFB_ENG_INTERNAL void        devconsole_toggle       (devconsole* dt);
    IFB_ENG_INTERNAL void        devconsole_render       (devconsole* dt);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct devconsole {
        devconsole_flags flags;
    };

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum devconsole_flag_e {
        devconsole_flag_e_none   = 0,
        devconsole_flag_e_active = bit_value(0) 
    }; 

};


#endif //IFB_ENGINE_GUI_INTERNAL_HPP