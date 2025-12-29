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
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr u64 MEMORY_MAP_SIZE_OS_RESOURCES    = size_megabytes(1);
    constexpr u64 MEMORY_MAP_SIZE_GRAPHICS        = size_megabytes(64);  

    constexpr u64 MEMORY_MAP_OFFSET_OS_RESOURCES  = 0; 
    constexpr u64 MEMORY_MAP_OFFSET_GRAPHICS      = MEMORY_MAP_SIZE_GRAPHICS;

    
    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void          memory_manager_startup  (void); 
    IFB_ENG_INTERNAL void          memory_manager_shutdown (void); 
    
    IFB_ENG_INTERNAL memory_block* memory_block_commit     (const memory_block_type block_type, const u32 size);
    IFB_ENG_INTERNAL void          memory_block_decommit   (memory_block* block);
    IFB_ENG_INTERNAL void          memory_block_reset      (memory_block* block);

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum memory_block_type_ {
        memory_block_type_os_resources = 0,
        memory_block_type_graphics     = 1,
        memory_block_type_count        = 2
    }; 

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct memory_block {
        void*             start;
        memory_block*     next;
        memory_block*     prev;
        memory_block_type type;
        u32               size;
    };

    struct memory_map {
        u64 start;
        u32 size_total;
        u32 size_commit;
        struct {
            memory_block* first;
        } commit_list;
    };


    struct memory_manager {
        struct {
            u32 block;
            u32 map;
        } granularity;
        union {
            struct {
                memory_map os_resources;
                memory_map graphics;
            };
            memory_map array[memory_block_type_count];
        } map;
    };
};

#endif //IFB_ENGINE_MEMORY_MANAGER_HPP