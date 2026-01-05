#ifndef ENTITY_MODULE_HPP
#define ENTITY_MODULE_HPP

#include "ifb-engine.hpp"
#include "managers.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct entity_module;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL entity_module* entity_module_init     (void);
    IFB_ENG_INTERNAL void           entity_module_startup  (void);
    IFB_ENG_INTERNAL void           entity_module_shutdown (void);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct entity_module {
        entity_manager* entity_manager;
    };
};

#endif //ENTITY_MODULE_HPP