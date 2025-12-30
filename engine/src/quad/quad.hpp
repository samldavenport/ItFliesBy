#ifndef IFB_ENG_QUAD_HPP
#define IFB_ENG_QUAD_HPP

#include "ifb-engine.hpp"
#include <sld-stack.hpp>
#include <math.hpp>

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

    struct quad {
        position  position;
        color_u32 color;
    };

    struct quad_memory {
        quad_memory* next;        
        quad_memory* prev;
        u32          start_index;        
    };

    struct quad_manager {
        u32 capacity;
        u32 count;
        struct {
            vec3*      position; 
            color_u32* color;
        } array;
    };
};

#endif //IFB_ENG_QUAD_HPP