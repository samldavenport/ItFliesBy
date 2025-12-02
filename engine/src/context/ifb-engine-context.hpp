#ifndef   IFB_ENGINE_CONTEXT_HPP
#define   IFB_ENGINE_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-os.hpp"

#include <sld-stack.hpp>

namespace ifb::eng {

    struct context;

    IFB_ENG_GLOBAL context* _context;


    struct context {
        stack       stack;
        os_context* os_mngr;
    };




};


#endif  //IFB_ENGINE_CONTEXT_HPP