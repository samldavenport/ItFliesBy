#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "ifb-engine.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct memory;
    struct memory_map;
    struct singleton_stack;
    struct arena;
    struct virtual_memory;
    struct reserved_memory;
    struct memory_commit;
    struct stack_allocator;
    struct block_allocator;
    struct arena_allocator;

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
    IFB_ENG_INTERNAL    memory_map* memory_map_create               (void);
    IFB_ENG_INTERNAL           void memory_map_destroy              (void);
    IFB_ENG_INTERNAL            u32 memory_map_align_to_page        (const u32 size);
    IFB_ENG_INTERNAL            u32 memory_map_align_to_granularity (const u32 size);

    // stack
    IFB_ENG_INTERNAL          void* singleton_alloc                 (const u32 size, const u32 alignment = 0);
    IFB_ENG_INTERNAL_TEMPLATE(t) t* singleton_alloc_struct          (const u32 count = 1);

    // virtual memory
    IFB_ENG_INTERNAL           void virtual_memory_acquire          (virtual_memory*  const vmem, reserved_memory* const rmem, const u32 size);
    IFB_ENG_INTERNAL          void* virtual_memory_commit           (virtual_memory*  const vmem, const u32 size, const u32 offset);
    IFB_ENG_INTERNAL           void virtual_memory_decommit         (virtual_memory*  const vmem, const );
    IFB_ENG_INTERNAL           void virtual_memory_validate         (virtual_memory*  const vmem);

    // arena
    IFB_ENG_INTERNAL         arena* arena_alloc                      (void);
    IFB_ENG_INTERNAL           void arena_validate                   (arena* const a);
    IFB_ENG_INTERNAL           void arena_free                       (arena* const a);
    IFB_ENG_INTERNAL           void arena_reset                      (arena* const a);
    IFB_ENG_INTERNAL            u32 arena_save                       (arena* const a);
    IFB_ENG_INTERNAL           void arena_revert                     (arena* const a, const u32 save);
    IFB_ENG_INTERNAL          void* arena_push                       (arena* const a, const u32 size, const u32 alignment = 0);
    IFB_ENG_INTERNAL_TEMPLATE(t) t* arena_push_struct                (arena* const a, const u32 count = 1);

    // stack allocator
    IFB_ENG_INTERNAL          void  stack_memory_allocator_init      (stack_allocator* const alctr, reserved_memory* const rmem, const u32 size, const u32 granularity = 0);
    IFB_ENG_INTERNAL          void  stack_memory_validate            (stack_allocator* const alctr);
    IFB_ENG_INTERNAL          void  stack_memory_reset               (stack_allocator* const alctr);
    IFB_ENG_INTERNAL          void* stack_memory_alloc               (stack_allocator* const alctr, const u32 size, const u32 alignment   = 0);
    IFB_ENG_INTERNAL_TEMPLATE(t) t* stack_memory_alloc_struct        (stack_allocator* const alctr, const u32 count = 1);
    IFB_ENG_INTERNAL          void  stack_memory_free                (stack_allocator* const alctr, void* memory);

    // block allocator
    IFB_ENG_INTERNAL          void  block_memory_allocator_init      (block_allocator* const alctr, reserved_memory const vmem, const u32 size_total, const u32 block_size);
    IFB_ENG_INTERNAL          void* block_memory_alloc               (block_allocator* const alctr);
    IFB_ENG_INTERNAL           void block_memory_free                (block_allocator* const alctr, void* block);
    IFB_ENG_INTERNAL           void block_memory_reset               (block_allocator* const alctr, void* block);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct memory {
        union {
            void* as_ptr;
            byte* as_bytes;
            addr  as_addr;
        } start;
        u64  size;
    };

    struct reserved_memory : memory {
        u64             position;
        u64             committed;
        struct {
            virtual_memory* first;
            virtual_memory* last;
        } vmem;

    };

    struct singleton_stack : stack { };

    struct arena {
        arena* next;
        arena* prev;
        u32    position;
        u32    save;
    };

    struct arena_allocator : memory {
        arena* first;
        u32    arena_size;
        u32    arena_capacity;
        u32    arena_count;
    };

    struct virtual_memory : memory {
        virtual_memory*  next;
        reserved_memory* rmem;
        u64              position;
    };

    struct os_reservation : memory {
        u32             granularity;
        u32             page_size;
        arena_allocator arena_allocator;
        struct {
            reserved_memory entities;
            reserved_memory graphics;
        } reserved_memory;
    };

    struct memory_map {
        singleton_stack singleton_stack;
        os_reservation  os_reservation;
    };

    struct block_allocator : memory {
        u32 block_capacity;
        u32 block_count;
        u32 block_size;
    };

    struct stack_allocator {
        virtual_memory* vmem;
        u32             offset;
        u32             size;
        u32             granularity;
        u32             page_capacity;
        u32             page_count;
        u32             page_position;
    };
};

#endif //MEMORY_HPP