#pragma once

#include "ifb-engine-context.hpp"

namespace ifb::eng {
    
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
        ctx->os = os_context_alloc(ctx->stack);

        return(ctx);        
    }

    IFB_ENG_API bool
    context_startup(
        context* ctx) {

        os_context_init(ctx->os);

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

        os_context_refresh_system_info (ctx->os);
        os_context_frame_start         (ctx->os);

        return(true);
    }

    IFB_ENG_API bool
    context_render(
        context* ctx) {

        assert(ctx);
        os_context_frame_render(ctx->os);
        return(true);
    }

    IFB_ENG_API bool
    context_should_quit(
        context* ctx) {

        return(false);
    }
};