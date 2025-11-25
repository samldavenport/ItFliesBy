#ifndef   IFB_ENGINE_CONTEXT_HPP
#define   IFB_ENGINE_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-os.hpp"

#include <sld-stack.hpp>

namespace ifb::eng {

    struct context {
        stack       stack;
        os_manager* os_mngr;

        void create_managers (void);
    };

};


#endif  //IFB_ENGINE_CONTEXT_HPP