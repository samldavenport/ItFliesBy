#ifndef IFB_ENG_QUAD_HPP
#define IFB_ENG_QUAD_HPP

#include "ifb-engine.hpp"
#include <sld-stack.hpp>

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct quad;
    struct quad_manager;
    struct quad_transform;
    struct quad_color;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    quad_manager* quad_manager_alloc    (stack& stack);
    void          quad_manager_startup  (quad_manager* mngr);
    void          quad_manager_shutdown (quad_manager* mngr);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------


};

#endif //IFB_ENG_QUAD_HPP