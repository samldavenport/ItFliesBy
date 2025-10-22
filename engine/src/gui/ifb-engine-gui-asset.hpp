#ifndef IFB_ENGINE_GUI_ASSET_HPP
#define IFB_ENGINE_GUI_ASSET_HPP

#include <ifb-engine-asset-config.hpp>

namespace ifb::eng {

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum gui_asset_flag_e : u32 {
        gui_asset_flag_e_none       = 0,
        gui_asset_flag_e_open_text  = sld::bit_value(1),
        gui_asset_flag_e_open_image = sld::bit_value(2),
        gui_asset_flag_e_open_sound = sld::bit_value(3),
        gui_asset_flag_e_open_font  = sld::bit_value(4),
        gui_asset_flag_e_config     = sld::bit_value(5),
        gui_asset_flag_e_database   = sld::bit_value(6)
    };

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------

    struct gui_asset_state_t;
    struct gui_asset_config_editor_t;
    using  gui_asset_flags_t = u32_t;

    IFB_ENG_INTERNAL        void gui_asset_render_config  (void);
    IFB_ENG_INTERNAL_INLINE void gui_asset_flag_set       (const gui_asset_flag_e flag);
    IFB_ENG_INTERNAL_INLINE bool gui_asset_flag_state     (const gui_asset_flag_e flag);
    IFB_ENG_INTERNAL_INLINE void gui_asset_flag_clear     (const gui_asset_flag_e flag);
    IFB_ENG_INTERNAL_INLINE void gui_asset_flag_reset_all (const gui_asset_flag_e flag);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct gui_asset_state_t {
        gui_asset_flags_t       flags;
        asset_config_context_t* config_context;
    }; 

    //-------------------------------------------------------------------
    // GLOBALS
    //-------------------------------------------------------------------

    IFB_ENG_GLOBAL asset_config_context_t _gui_asset_config_context;
    IFB_ENG_GLOBAL gui_asset_state_t      _gui_asset_state = {
        { gui_asset_flag_e_none }, // flags
        &_gui_asset_config_context // config_context
    };

    //-------------------------------------------------------------------
    // INLINE METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL_INLINE void
    gui_asset_flag_set(
        const gui_asset_flag_e flag) {

        _gui_asset_state.flags.val |= flag;
    }

    IFB_ENG_INTERNAL_INLINE bool
    gui_asset_flag_state(
        const gui_asset_flag_e flag) {

        return(_gui_asset_state.flags.val & flag);
    }

    IFB_ENG_INTERNAL_INLINE void
    gui_asset_flag_clear(
        const gui_asset_flag_e flag) {

        _gui_asset_state.flags.val &= ~flag;
    }

    IFB_ENG_INTERNAL_INLINE void
    gui_asset_flag_reset_all(
        void) {

        _gui_asset_state.flags.val = gui_asset_flag_e_none;
    }
};

#endif //IFB_ENGINE_GUI_ASSET_HPP