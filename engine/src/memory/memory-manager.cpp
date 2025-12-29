#pragma once

#include "memory.hpp"
#include "ifb-engine-context.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    memory_manager_alloc(
        void) {

        _memory_manager = context_stack_alloc<memory_manager>();
        assert(_memory_manager);
    }

    IFB_ENG_INTERNAL void
    memory_manager_startup(
        void) {


    } 

    IFB_ENG_INTERNAL void
    memory_manager_shutdown(
        void) {

    } 

    IFB_ENG_INTERNAL void*
    memory_manager_block_alloc(
        const memory_block_type block_type) {

    }

    IFB_ENG_INTERNAL void
    memory_manager_block_free(
        const memory_block_type block_type,
        const void*             memory) {

    }


};