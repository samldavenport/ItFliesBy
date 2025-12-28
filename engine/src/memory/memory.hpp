#ifndef IFB_ENGINE_MEMORY_MANAGER_HPP
#define IFB_ENGINE_MEMORY_MANAGER_HPP


#include "ifb-engine.hpp"


namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct memory_reservation;
    struct memory_block;
    struct memory_manager;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    void memory_manager_alloc()


    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct memory_reservation {
        addr start;
        u32  size_kb_total;
        u32  size_kb_commit_min;
    };

    struct memory_block {
        u32 offset_kb;
        u32 size_kb_total;
        u32 size_kb_commit;
    };

    struct memory_manager {
        memory_reservation reservation;
        struct {
            memory_block quads;
            memory_block vertex_buffers;
        } block;
    };



};

#endif //IFB_ENGINE_MEMORY_MANAGER_HPP