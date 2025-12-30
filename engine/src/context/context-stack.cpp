#pragma once

#include "context.hpp"

namespace ifb::eng {



    IFB_ENG_INTERNAL devconsole*
    context_stack_alloc_devconsole(
        void) {

        devconsole* console = context_stack_alloc<devconsole>();
        assert(console);

        return(console);
    }

};