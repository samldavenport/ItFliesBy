#ifndef   IFB_ENGINE_CONTEXT_HPP
#define   IFB_ENGINE_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-os.hpp"
#include "ifb-engine-devconsole.hpp"
#include "memory.hpp"
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
        devconsole*          devconsole;
        context_keymap_flags keymap_flags;
        struct {
            os_manager*       os;
            graphics_manager* graphics;
            memory_manager*   memory;
        } manager;
    };

    template<typename t>
    inline t*
    context_stack_alloc(
        const u32 count = 1) {

        assert(_context);
        t* mem = _context->stack.push_struct<t>();
        return(mem);
    }

    inline os_manager*
    context_os_manager(
        void) {

        assert(
            _context             != NULL && 
            _context->manager.os != NULL
        );

        return(_context->manager.os);
    }

    inline graphics_manager*
    context_graphics_manager(
        void) {

        assert(
            _context                   != NULL &&
            _context->manager.graphics != NULL
        );
        return(_context->manager.graphics);
    }

    inline memory_manager*
    context_memory_manager(
        void) {

        assert(
            _context                 != NULL &&
            _context->manager.memory != NULL
        );
        return(_context->manager.memory);
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