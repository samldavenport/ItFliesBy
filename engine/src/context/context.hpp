#ifndef   IFB_ENGINE_CONTEXT_HPP
#define   IFB_ENGINE_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "os-module.hpp"
#include "devconsole.hpp"
#include "memory-module.hpp"
#include "graphics-module.hpp"

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

    // stack
    IFB_ENG_INTERNAL devconsole*       context_stack_alloc_devconsole       (void);


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
        devconsole*          devconsole;
        context_keymap_flags keymap_flags;
        struct {
            os_module*       os;
            graphics_module* graphics;
            memory_module*   memory;
        } module;
    };

    template<typename t>
    inline t*
    context_stack_alloc(
        const u32 count = 1) {

        assert(_context);
        t* mem = _context->stack.push_struct<t>();
        return(mem);
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