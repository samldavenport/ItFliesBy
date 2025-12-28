#ifndef   IFB_ENGINE_CONTEXT_HPP
#define   IFB_ENGINE_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-os.hpp"
#include "ifb-engine-devconsole.hpp"
#include "graphics.hpp"

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

    using context_keymap_flags = u32;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void context_process_keycodes (context* ctx);

    //-------------------------------------------------------------------
    // GLOBAL
    //-------------------------------------------------------------------

    static context* _context;

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct context_flags {
        context_keymap_flags keymap;
    };

    struct context {
        stack                stack;
        os_context*          os;
        devconsole*          devconsole;
        graphics_manager*    graphics_manager;
        context_keymap_flags keymap_flags;
    };

    template<typename t>
    inline t*
    context_stack_alloc(
        const u32 count = 1) {

        assert(_context);
        t* mem = _context->stack.push_struct<t>();
        return(mem);
    }

    inline os_context*
    context_os(
        void) {

        assert(
            _context     != NULL && 
            _context->os != NULL
        );

        return(_context->os);
    }

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum context_keymap_flag_e {
        context_keymap_flag_e_none       = 0,
        context_keymap_flag_e_devconsole = bit_value(0)
    };
};


#endif  //IFB_ENGINE_CONTEXT_HPP