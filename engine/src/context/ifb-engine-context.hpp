#ifndef   IFB_ENGINE_CONTEXT_HPP
#define   IFB_ENGINE_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-os.hpp"

#include <sld-stack.hpp>

namespace ifb::eng {

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr input_keycode CONTEXT_KEYCODE_DEVTOOLS = IFB_ENG_CONFIG_CONTEXT_KEYCODE_DEVTOOLS;

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct context;
    struct context_flags;

    using context_gui_flags    = u32;
    using context_keymap_flags = u32;

    IFB_ENG_INTERNAL void context_process_keycodes (context* ctx);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct context_flags {
        context_gui_flags    gui;
        context_keymap_flags keymap;
    };

    struct context {
        stack         stack;
        os_context*   os;
        context_flags flags;
    };

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum context_keymap_flag_e {
        context_keymap_flag_e_none     = 0,
        context_keymap_flag_e_devtools = bit_value(0)
    };

    enum context_gui_flag_e {
        context_gui_flag_e_none       = 0,
        context_gui_flag_e_devtools   = 1,
        context_gui_flag_e_imgui_demo = 2
    };
};


#endif  //IFB_ENGINE_CONTEXT_HPP