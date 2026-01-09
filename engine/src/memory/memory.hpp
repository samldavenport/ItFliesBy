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
    struct memory_reservation;
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
    IFB_ENG_INTERNAL      memory_map* memory_map_create             (void);
    IFB_ENG_INTERNAL             void memory_map_destroy            (void);

    // reservation
    IFB_ENG_INTERNAL            void* virtual_memory_commit         (virtual_memory* const vmem, const u32 offset, const u32 size);
    IFB_ENG_INTERNAL             void virtual_memory_decommit       (virtual_memory* const vmem, void* memory);
    IFB_ENG_INTERNAL              u32 virtual_memory_size_committed (virtual_memory* const vmem);
    IFB_ENG_INTERNAL              u32 virtual_memory_size_total     (virtual_memory* const vmem);
    IFB_ENG_INTERNAL             void virtual_memory_get_info       (virtual_memory* const vmem, memory_region_info& info);

    // stack
    IFB_ENG_INTERNAL            void* singleton_alloc               (const u32 size, const u32 alignment = 0);
    IFB_ENG_INTERNAL_TEMPLATE(t)   t* singleton_alloc_struct        (const u32 count = 1);

    // arena
    IFB_ENG_INTERNAL           arena* arena_alloc                   (void);
    IFB_ENG_INTERNAL             void arena_validate                (arena* const arena);
    IFB_ENG_INTERNAL             void arena_free                    (arena* const arena);
    IFB_ENG_INTERNAL             void arena_reset                   (arena* const arena);
    IFB_ENG_INTERNAL              u32 arena_save                    (arena* const arena);
    IFB_ENG_INTERNAL             void arena_revert                  (arena* const arena, const u32 save);
    IFB_ENG_INTERNAL            void* arena_push                    (arena* const arena, const u32 size, const u32 alignment = 0);
    IFB_ENG_INTERNAL_TEMPLATE(t)   t* arena_push_struct             (arena* const arena, const u32 count = 1);

    // stack allocator
    IFB_ENG_INTERNAL stack_allocator* stack_allocator_init          (virtual_memory*  const vmem,   const u32 size, const u32 granularity = 0);
    IFB_ENG_INTERNAL            void* stack_alloc                   (stack_allocator* const alctr,  const u32 size, const u32 alignment   = 0);
    IFB_ENG_INTERNAL_TEMPLATE(t)   t* stack_alloc_struct            (stack_allocator* const alctr,  const u32 count = 1);
    IFB_ENG_INTERNAL            void  stack_free                    (stack_allocator* const alctr,  void* memory);

    // block allocator
    IFB_ENG_INTERNAL block_allocator* block_allocator_init          (virtual_memory*  const vmem, const u32 size_total, const u32 block_size);
    IFB_ENG_INTERNAL            void* block_alloc                   (block_allocator* const alctr);
    IFB_ENG_INTERNAL             void block_free                    (block_allocator* const alctr, void* block);

    //-------------------------------------------------------------------
    // STACK ALLOCATOR
    //-------------------------------------------------------------------

    struct stack_allocator : memory {

        u32  granularity;
        u32  page_capacity;
        u32  page_size;
        u32  page_count;
        u32  page_position;
        u32  page_alignment;

        explicit stack_allocator(
            memory_region& region,
            const u32      granularity_min,
            const u32      page_size_min
        );

        void  validate  (void) const;
        void  reset     (void);
        void* push      (const u32 size, const u32 alignment = 0);
        void  pull      (const u32 size, const u32 alignment = 0);
        void  save      (void);
        void  roll_back (void);

        template<typename t> t*   push_struct (const u32 count = 1);
        template<typename t> void pull_struct (const u32 count = 1);
    };

    //-------------------------------------------------------------------
    // BLOCK ALLOCATOR
    //-------------------------------------------------------------------

    struct block_allocator : memory {

        u32 block_capacity;
        u32 block_count;
        u32 block_size;
    };

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

    struct singleton_stack : stack { };

    struct arena {
        arena* next;
        arena* prev;
        u32    position;
        u32    save;
    };

    struct arena_allocator : memory {
        arena* first;
        u32 arena_size;
        u32 arena_capacity;
        u32 arena_count;
    };

    struct virtual_memory : memory {
        u32 granularity;
        u32 position;
    };

    struct os_reservation : memory {
        u32             granularity;
        u32             page_size;
        arena_allocator arena_list;
        struct {
            virtual_memory entities;
            virtual_memory graphics;
        } virtual_memory;
    };

    struct memory_map {
        singleton_stack singleton_stack;
        os_reservation  os_reservation;
    };
};

#endif //MEMORY_HPP