#ifndef IFB_ENGINE_GUI_IMGUI_HPP
#define IFB_ENGINE_GUI_IMGUI_HPP

#include "ifb-engine.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum gui_imgui_flag_e : u32 {
        gui_imgui_flag_e_none      = 0,
        gui_imgui_flag_e_base_demo = sld::bit_value(0),
        gui_imgui_flag_e_plot_demo = sld::bit_value(1)
    };

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------

    struct gui_imgui_state_t;
    using  gui_imgui_flags_t = u32_t;

    IFB_ENG_INTERNAL        void gui_imgui_render         (void);
    IFB_ENG_INTERNAL_INLINE void gui_imgui_flag_set       (const gui_imgui_flag_e flag);
    IFB_ENG_INTERNAL_INLINE bool gui_imgui_flag_state     (const gui_imgui_flag_e flag);
    IFB_ENG_INTERNAL_INLINE void gui_imgui_flag_clear     (const gui_imgui_flag_e flag);
    IFB_ENG_INTERNAL_INLINE void gui_imgui_flag_reset_all (void);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------
    
    struct gui_imgui_state_t {
        gui_imgui_flags_t flags;
    };

    //-------------------------------------------------------------------
    // GLOBALS
    //-------------------------------------------------------------------

    IFB_ENG_GLOBAL gui_imgui_state_t _gui_imgui_state;

    //-------------------------------------------------------------------
    // INLINE METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL_INLINE void
    gui_imgui_flag_set(
        const gui_imgui_flag_e flag) {

        _gui_imgui_state.flags.val |= flag;
    }

    IFB_ENG_INTERNAL_INLINE bool
    gui_imgui_flag_state(
        const gui_imgui_flag_e flag) {

        return(_gui_imgui_state.flags.val & flag);
    }

    IFB_ENG_INTERNAL_INLINE void
    gui_imgui_flag_clear(
        const gui_imgui_flag_e flag) {

        _gui_imgui_state.flags.val &= ~flag;
    }

    IFB_ENG_INTERNAL_INLINE void
    gui_imgui_flag_reset_all(
        void) {

        _gui_imgui_state.flags.val = gui_imgui_flag_e_none;
    }
};

#endif //IFB_ENGINE_GUI_IMGUI_HPP