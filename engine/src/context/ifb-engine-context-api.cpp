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

        // initialize the stack
        ctx->stack.init(stack_data, stack_size);

        // initialize managers
        ctx->os_mngr = os_manager_stack_alloc(ctx->stack);



        return(ctx);        
    }

    IFB_ENG_API bool
    context_startup(
        context* ctx) {

        return(false);
    }

    IFB_ENG_API bool
    context_shutdown(
        context* ctx) {

        return(false);
    }

    IFB_ENG_API bool
    context_update(
        context* ctx) {

        return(false);
    }

    IFB_ENG_API bool
    context_render(
        context* ctx) {

        return(false);
    }

    IFB_ENG_API bool
    context_should_quit(
        context* ctx) {

        return(true);
    }
};