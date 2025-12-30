#pragma once

#include "context.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL graphics_manager*
    context_stack_alloc_graphics_manager(
        void) {

        auto mngr       = context_stack_alloc<graphics_manager>();
        auto hello_quad = context_stack_alloc<graphics_renderer>();
    
        bool did_alloc = true;
        did_alloc &= (mngr       != NULL); 
        did_alloc &= (hello_quad != NULL);
        assert(did_alloc);

        mngr->hello_quad_renderer = hello_quad;

        return(mngr); 
    }

    IFB_ENG_INTERNAL memory_manager*
    context_stack_alloc_memory_manager(
        void) {

        auto mngr = context_stack_alloc<memory_manager>();
        assert(mngr);
        return(mngr);
    }

    IFB_ENG_INTERNAL devconsole*
    context_stack_alloc_devconsole(
        void) {

        devconsole* console = context_stack_alloc<devconsole>();
        assert(console);

        return(console);
    }

};