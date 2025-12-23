#pragma once

#include "ifb-engine-context.hpp"
#include "gl.hpp"
namespace ifb::eng {
    
    constexpr u32 OS_WINDOW_KEYCODE_CAPACITY         = IFB_ENG_CONFIG_OS_WINDOW_KEYCODE_CAPACITY;
    constexpr u32 OS_WINDOW_DEFAULT_WIDTH            = IFB_ENG_CONFIG_OS_WINDOW_DEFAULT_WIDTH;
    constexpr u32 OS_WINDOW_DEFAULT_HEIGHT           = IFB_ENG_CONFIG_OS_WINDOW_DEFAULT_HEIGHT;
    constexpr u32 OS_WINDOW_DEFAULT_CLEAR_COLOR_RGBA = IFB_ENG_CONFIG_OS_WINDOW_DEFAULT_CLEAR_COLOR_RGBA;

    static gl_hello_triangle _hello_triangle;

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

        // initialize the stack and allocate structures
        ctx->stack.init(ctx_stack_data, ctx_stack_size);
        ctx->os         = os_context_alloc (ctx->stack);
        ctx->devconsole = devconsole_alloc   (ctx->stack);

        assert(
            ctx->stack.is_valid() &&
            ctx->os       != NULL &&
            ctx->devconsole != NULL
        );

        return(ctx);        
    }

    IFB_ENG_API bool
    context_startup(
        context* ctx) { 

        assert(ctx);

        // os context        
        os_system_refresh_info    (ctx->os);
        os_memory_reserve         (ctx->os);
        os_monitor_refresh_table  (ctx->os);
        os_window_create_and_show (ctx->os);

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

        // hello triangle test program
        gl_hello_triangle_create(_hello_triangle);

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
        os_system_refresh_info   (ctx->os);
        os_monitor_refresh_table (ctx->os);
        os_memory_check_usage    (ctx->os);

        // process events and input
        os_window_start_frame_and_process_events (ctx->os);
        context_process_keycodes                 (ctx);

        // reset window events and input
        os_window_reset_events (ctx->os);
        os_window_reset_input  (ctx->os);

        return(true);
    }

    IFB_ENG_API bool
    context_render(
        context* ctx) {

        assert(ctx);

        devconsole_render(ctx->devconsole);
        gl_hello_triangle_render(_hello_triangle);
        os_window_render_frame(ctx->os);

        return(true);
    }

    IFB_ENG_API bool
    context_should_quit(
        context* ctx) {

        const bool should_quit = os_window_should_quit(ctx->os);

        return(should_quit);
    }
};