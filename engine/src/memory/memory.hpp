#ifndef IFB_ENGINE_MEMORY_MANAGER_HPP
#define IFB_ENGINE_MEMORY_MANAGER_HPP


#include "ifb-engine.hpp"


namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct memory_manager;
    struct memory_block;

    using memory_block_type = u32;

    //-------------------------------------------------------------------
    // GLOBAL
    //-------------------------------------------------------------------

    static memory_manager* _memory_manager;

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr u32 MEMORY_BLOCK_QUAD_SIZE_KB_TOTAL           = 1024;  // 1MB
    constexpr u32 MEMORY_BLOCK_QUAD_SIZE_KB_COMMIT          = 4;     // 4KB
    constexpr u32 MEMORY_BLOCK_VERTEX_BUFFER_SIZE_KB_TOTAL  = 65536; // 64MB
    constexpr u32 MEMORY_BLOCK_VERTEX_BUFFER_SIZE_KB_COMMIT = 64;    // 64KB

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void  memory_manager_init        (void);
    IFB_ENG_INTERNAL void  memory_manager_startup     (void); 
    IFB_ENG_INTERNAL void  memory_manager_shutdown    (void); 
    IFB_ENG_INTERNAL void* memory_manager_block_alloc (const memory_block_type block_type);
    IFB_ENG_INTERNAL void  memory_manager_block_free  (const memory_block_type block_type, const void* memory);

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum memory_block_type_ {
        memory_block_type_quad          = 0,
        memory_block_type_vertex_buffer = 1,
        memory_block_type_count         = 2
    }; 

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct memory_block {
        u32 offset_kb;
        u32 size_total;
        u32 size_commit;
        u32 commit_count;
    };

    struct memory_manager {
        addr reservation_start;
        union {
            struct {
                memory_block quads;
                memory_block vertex_buffers;
            };
            memory_block array[memory_block_type_count];
        } block;
    };
};

#endif //IFB_ENGINE_MEMORY_MANAGER_HPP