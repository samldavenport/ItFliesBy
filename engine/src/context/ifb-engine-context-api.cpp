#pragma once

#include "ifb-engine-context.hpp"

namespace ifb::eng {
    
    IFB_ENG_API context_t*
    context_create(
        byte*     stack_data,
        const u64 stack_size) {

        assert(
            stack_data != NULL &&
            stack_size != 0
        );
     
        memset(stack_data, 0, stack_size);

        const u64  context_size       = sizeof(context_t);
        const u64  context_stack_size = stack_size - context_size;
        byte*      context_stack_data = stack_data + context_size;  
        context_t* context            = (context_t*)stack_data; 

        context_init_stack    (context, context_stack_data, context_stack_size);
        context_init_managers (context);

        return(context);        
    }

    IFB_ENG_API bool
    context_startup(
        context_t* context) {

        return(false);
    }

    IFB_ENG_API bool
    context_shutdown(
        context_t* context) {

        return(false);
    }

    IFB_ENG_API bool
    context_update(
        context_t* context) {

        return(false);
    }

    IFB_ENG_API bool
    context_render(
        context_t* context) {

        return(false);
    }

    IFB_ENG_API bool
    context_should_quit(
        context_t* context) {

        return(true);
    }
};