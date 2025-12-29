 #pragma once

#include "ifb-engine-context.hpp"
#include "gl.hpp"
namespace ifb::eng {
    
    constexpr u32 OS_WINDOW_KEYCODE_CAPACITY         = IFB_ENG_CONFIG_OS_WINDOW_KEYCODE_CAPACITY;
    constexpr u32 OS_WINDOW_DEFAULT_WIDTH            = IFB_ENG_CONFIG_OS_WINDOW_DEFAULT_WIDTH;
    constexpr u32 OS_WINDOW_DEFAULT_HEIGHT           = IFB_ENG_CONFIG_OS_WINDOW_DEFAULT_HEIGHT;
    constexpr u32 OS_WINDOW_DEFAULT_CLEAR_COLOR_RGBA = IFB_ENG_CONFIG_OS_WINDOW_DEFAULT_CLEAR_COLOR_RGBA;

    IFB_ENG_API context*
    context_create(
        byte*     stack_data,
        const u64 stack_size) {

        assert(
            stack_data != NULL &&
            stack_size != 0
        );

        // cast context     
        memset(stack_data, 0, stack_size);
        const u64  ctx_size       = sizeof(context);
        const u64  ctx_stack_size = stack_size - ctx_size;
        byte*      ctx_stack_data = stack_data + ctx_size;  
        context*   ctx            = (context*)stack_data; 
        _context = ctx;

        // initialize the stack and allocate structures
        ctx->stack.init(ctx_stack_data, ctx_stack_size);
        os_manager_alloc       (ctx->stack);
        ctx->devconsole       = devconsole_alloc       (ctx->stack);
        ctx->manager.graphics = graphics_manager_alloc (ctx->stack);

        assert(
            ctx->stack.is_valid()         &&
            ctx->devconsole       != NULL &&
            ctx->manager.os       != NULL &&
            ctx->manager.graphics != NULL
        );


        return(ctx);        
    }

    IFB_ENG_API bool
    context_startup(
        context* ctx) { 

        assert(ctx);

        // os context        
        os_system_refresh_info    ();
        os_memory_reserve         ();
        os_monitor_refresh_table  ();
        os_window_create_and_show ();

        // devconsole
        devconsole_init(ctx->devconsole);

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
        graphics_manager_startup(ctx->manager.graphics);

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
        os_system_refresh_info   ();
        os_monitor_refresh_table ();
        os_memory_check_usage    ();

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

        devconsole_render(ctx->devconsole);
        graphics_manager_render_hello_quad(ctx->manager.graphics);
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