#pragma once

#include "ifb-engine-context.hpp"

namespace ifb::eng {


    IFB_ENG_INTERNAL void
    context_init_stack(
        context_t* context,
        byte*      stack_data,
        const u64  stack_size) {

        assert(
            context    != NULL &&
            stack_size != 0    &&
            stack_data != NULL
        );

        context->stack.init(stack_data, stack_size);
        context->stack.assert_valid();
    }

    IFB_ENG_INTERNAL void
    context_init_managers(
        context_t* context) {

        context->memory_mngr = context_stack_push_struct<memory_manager_t> (context);
        context->file_mngr   = context_stack_push_struct<file_manager_t>   (context);
    }
    
    template<typename struct_type_t>
    IFB_ENG_INTERNAL struct_type_t*
    context_stack_push_struct(
        context_t* context) {

        assert(context);
        context->stack.assert_valid();

        struct_type_t* type = context->stack.push_struct<struct_type_t>();
        assert(type);

        return(type);
    }
};