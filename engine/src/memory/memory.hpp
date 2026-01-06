#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "ifb-engine.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct memory;
    struct memory_map;
    struct memory_arena;
    struct memory_region;
    struct memory_reservation;
    struct memory_map_info;
    struct memory_stack_info;
    struct memory_os_reservation_info;
    struct memory_region_info;
    struct memory_commit;

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr u32 MEMORY_ARENA_SIZE                  = size_kilobytes(64);
    constexpr u32 MEMORY_STACK_SIZE                  = size_kilobytes(64);
    
    // region sizes
    constexpr u32 MEMORY_REGION_SIZE_ARENAS          = size_megabytes(64);
    constexpr u32 MEMORY_REGION_SIZE_ENTITIES        = size_megabytes(64);
    constexpr u32 MEMORY_REGION_SIZE_GRAPHICS        = size_megabytes(64);

    // region offsets
    constexpr u32 MEMORY_REGION_OFFSET_ARENAS        = 0;
    constexpr u32 MEMORY_REGION_OFFSET_ENTITIES      = MEMORY_REGION_OFFSET_ARENAS;
    constexpr u32 MEMORY_REGION_OFFSET_GRAPHICS      = MEMORY_REGION_OFFSET_ENTITIES + MEMORY_REGION_SIZE_ENTITIES;

    // region granularities
    constexpr u32 MEMORY_REGION_GRANULARITY_ARENAS   = MEMORY_ARENA_SIZE;
    constexpr u32 MEMORY_REGION_GRANULARITY_ENTITIES = size_kilobytes(4);
    constexpr u32 MEMORY_REGION_GRANULARITY_GRAPHICS = size_kilobytes(64);

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    // map
    IFB_ENG_INTERNAL memory_map*    memory_map_create                (void);
    IFB_ENG_INTERNAL void           memory_map_destroy               (void);
    IFB_ENG_INTERNAL void           memory_map_get_info              (memory_map_info& info);

    // region
    IFB_ENG_INTERNAL void*          memory_region_commit             (memory_region* const region);
    IFB_ENG_INTERNAL void           memory_region_decommit           (memory_region* const region, void* memory);
    IFB_ENG_INTERNAL u32            memory_region_commit_granularity (memory_region* const region);
    IFB_ENG_INTERNAL u32            memory_region_size_committed     (memory_region* const region);
    IFB_ENG_INTERNAL u32            memory_region_size_total         (memory_region* const region);
    IFB_ENG_INTERNAL void           memory_region_get_info           (memory_region* const region, memory_region_info& info);

    // stack
    IFB_ENG_INTERNAL          void* memory_stack_alloc               (const u32 size, const u32 alignment = 0);
    IFB_ENG_INTERNAL_TEMPLATE(t) t* memory_stack_alloc_struct        (const u32 count = 1);
    IFB_ENG_INTERNAL           void memory_stack_get_info            (memory_stack_info& info);

    // arena
    IFB_ENG_INTERNAL  memory_arena* memory_arena_alloc               (void);
    IFB_ENG_INTERNAL           void memory_arena_validate            (memory_arena* const arena);
    IFB_ENG_INTERNAL           void memory_arena_free                (memory_arena* const arena);
    IFB_ENG_INTERNAL           void memory_arena_reset               (memory_arena* const arena);
    IFB_ENG_INTERNAL            u32 memory_arena_save                (memory_arena* const arena);
    IFB_ENG_INTERNAL           void memory_arena_revert              (memory_arena* const arena, const u32 save);
    IFB_ENG_INTERNAL          void* memory_arena_push                (memory_arena* const arena, const u32 size, const u32 alignment = 0);
    IFB_ENG_INTERNAL_TEMPLATE(t) t* memory_arena_push_struct         (memory_arena* const a, const u32 count = 1);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct memory {
        union {
            void* as_ptr;
            byte* as_bytes;
            addr  as_addr;
        };
        u64  size;
    };

    struct memory_region_info {
        u32 size_total;
        u32 size_committed;
    };

    struct memory_os_reservation_info {
        u32 size_kb_total;
        u32 size_kb_committed;
        u32 granularity;
        u32 page_size;
    };

    struct memory_stack_info {
        u32 size_total;
        u32 size_used;
    };

    struct memory_map_info {
        memory_stack_info          stack;
        memory_os_reservation_info os_reservation;
        struct {
            memory_region_info arenas;
            memory_region_info graphics;
            memory_region_info entities;
        } region;
    };

};

#endif //MEMORY_HPP