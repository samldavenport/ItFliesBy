 #pragma once

#include "context.hpp"
#include "gl.hpp"
#include "system.hpp"
#include "memory.hpp"

namespace ifb::eng {
    
    constexpr u32 OS_WINDOW_KEYCODE_CAPACITY         = IFB_ENG_CONFIG_OS_WINDOW_KEYCODE_CAPACITY;
    constexpr u32 OS_WINDOW_DEFAULT_WIDTH            = IFB_ENG_CONFIG_OS_WINDOW_DEFAULT_WIDTH;
    constexpr u32 OS_WINDOW_DEFAULT_HEIGHT           = IFB_ENG_CONFIG_OS_WINDOW_DEFAULT_HEIGHT;
    constexpr u32 OS_WINDOW_DEFAULT_CLEAR_COLOR_RGBA = IFB_ENG_CONFIG_OS_WINDOW_DEFAULT_CLEAR_COLOR_RGBA;

    IFB_ENG_API context*
    context_create(
        void) {

        system_refresh_info();
        memory_map* map = memory_map_create();

        _context = memory_stack_alloc_struct<context>();
        assert(_context);

        // initialize the stack and allocate structures
        _context->module.os        = os_module_init();
        _context->module.graphics  = graphics_module_init(); 
        _context->devconsole       = devconsole_init(); 
        _context->mem_map          = map;

        assert(
            _context->devconsole       != NULL &&
            _context->module.graphics != NULL
        );

        return(_context);        
    }

    IFB_ENG_API bool
    context_startup(
        context* ctx) { 

        assert(ctx);

        // os context        
        system_refresh_info();
        os_monitor_refresh_table  ();
        os_window_create_and_show ();

        // initialize gl context
        gl_context_init();
        gl_context_enable_smoothing();
        gl_context_enable_depth_rendering();
        gl_context_set_clear_color(OS_WINDOW_DEFAULT_CLEAR_COLOR_RGBA);
        gl_context_set_viewport(
            0,0,
            IFB_ENG_CONFIG_OS_WINDOW_DEFAULT_WIDTH,
            IFB_ENG_CONFIG_OS_WINDOW_DEFAULT_HEIGHT
        );

        // graphics
        graphics_module_startup();

        // start gui
        devconsole_start_gui();

        // arena test
        memory_arena* arena_0 = memory_arena_alloc();
        memory_arena* arena_1 = memory_arena_alloc();
        memory_arena* arena_2 = memory_arena_alloc();

        memory_arena_free(arena_1);
        memory_arena_free(arena_0);
        memory_arena_free(arena_2);

        return(true);
    }

    IFB_ENG_API bool
    context_shutdown(
        context* ctx) {

        return(true);
    }

    IFB_ENG_API bool
    context_update(
        context* ctx) {

        assert(ctx);

        // clear the viewport
        gl_context_clear_viewport();

        // check system resources
        system_refresh_info      ();
        os_monitor_refresh_table ();

        // process events and input
        os_window_start_frame_and_process_events ();
        context_process_keycodes                 (ctx);

        // reset window events and input
        os_window_reset_events ();
        os_window_reset_input  ();

        return(true);
    }

    IFB_ENG_API bool
    context_render(
        context* ctx) {

        assert(ctx);

        devconsole_render();
        graphics_module_render_hello_quad();
        os_window_render_frame();

        return(true);
    }

    IFB_ENG_API bool
    context_should_quit(
        context* ctx) {

        const bool should_quit = os_window_should_quit();

        return(should_quit);
    }
};