#pragma once

#include "memory.hpp"
#include "memory-map.cpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct memory_arena {
        memory_arena* next;
        memory_arena* prev;
        u32           position;
        u32           save;
    };

    struct memory_arena_list {
        memory_arena* first;
    };

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr u32 MEMORY_ARENA_SIZE_ACTUAL = (MEMORY_ARENA_SIZE - sizeof(memory_arena));
    
    //-------------------------------------------------------------------
    // GLOBAL
    //-------------------------------------------------------------------

    static memory_arena_list _arena_list;    

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL memory_arena*
    memory_arena_alloc(
        void) {

        assert(_map);

        const u32     arena_count  = _map->region.arenas.commit_count;
        const u32     arena_stride = _map->region.arenas.commit_granularity;
        const addr    arena_region = _map->region.arenas.as_addr; 
        memory_arena* arena        = NULL;

        for_count_u32(arena_index, arena_count) {

            const u32  arena_offset = (arena_stride * arena_count);
            void*      arena_start  = (void*)(arena_region + arena_offset); 
            const bool is_free      = !os_memory_is_committed(arena_start); 

            if(is_free) {

                arena = (memory_arena*)sld::os_memory_commit(arena_start, arena_stride);
                assert((void*)arena == arena_start);

                ++_map->region.arenas.commit_count;

                arena->position   = 0;
                arena->save       = 0;
                arena->prev       = NULL;
                arena->next       = _arena_list.first;
                _arena_list.first = arena;
            }
        }

        return(arena);
    }

    IFB_ENG_INTERNAL void
    memory_arena_validate(
        memory_arena* const arena) {

        bool is_valid = (arena != NULL);
        if (is_valid) {

            // get arena info
            const u32  arena_stride = _map->region.arenas.commit_granularity;
            const addr arena_min    = _map->region.arenas.as_addr;
            const addr arena_max    = (arena_min + _map->region.arenas.size) - arena_stride;
            const addr arena_start  = (addr)arena;
            const addr arena_offset = (arena_start - _map->os_reservation.as_addr);

            // ensure the arena is within the region
            // and aligned by granularity
            is_valid &= (arena_start  >= arena_min);
            is_valid &= (arena_start  <= arena_max);
            is_valid &= (arena_offset %  arena_stride == 0);
            is_valid &= (arena->position < MEMORY_ARENA_SIZE_ACTUAL);
            is_valid &= (arena->save     < arena->position);
        }
        assert(is_valid);
    }

    IFB_ENG_INTERNAL void
    memory_arena_free(
        memory_arena* const arena) {

        memory_arena_validate(arena);

        // remove from the list
        memory_arena* arena_next = arena->next;
        memory_arena* arena_prev = arena->prev;
        if (arena_prev == NULL) {
            _arena_list.first = arena_next;
            arena_next->prev  = NULL;
        }
        else {
            arena_prev->next = arena_next;
        }
        if (arena_next) {
            arena_next->prev = arena_prev;
        }

        // decommit and adjust the count
        const bool did_decommit = sld::os_memory_decommit(
            (void*)arena,
            _map->region.arenas.commit_granularity
        );
        assert(did_decommit);
        _map->region.arenas.commit_count--;
    }

    IFB_ENG_INTERNAL void
    memory_arena_reset(
        memory_arena* const arena) {

        memory_arena_validate(arena);

        arena->position = 0;
        arena->save     = 0;
    }

    IFB_ENG_INTERNAL u32
    memory_arena_save(
        memory_arena* const arena) {

        memory_arena_validate(arena);
        assert(arena->save == 0);

        arena->save = arena->position;
        return(arena->save);
    }

    IFB_ENG_INTERNAL void
    memory_arena_revert(
        memory_arena* const arena,
        const u32           save) {

        memory_arena_validate(arena);
        assert(
            arena->save == save &&
            arena->save != 0    &&
            save    != 0
        );

        arena->position = arena->save;
        arena->save     = 0;
    }

    IFB_ENG_INTERNAL void*
    memory_arena_push(
        memory_arena* const arena,
        const u32           size,
        const u32           alignment) {

        // check args
        memory_arena_validate(arena);
        assert(size != 0);

        // align the size
        const u32 size_aligned = size_is_pow_2(alignment)
            ? size_align_pow_2 (size, alignment)
            : size_align       (size, alignment);

        // check if we can fit the push
        const u32  new_position = (arena->position  + size_aligned);
        const bool can_push     = (new_position < MEMORY_ARENA_SIZE_ACTUAL); 
        if (!can_push) return(NULL);

        // calculate the pointer
        const addr start = (addr)arena;
        void*      ptr   = (void*)(start + arena->position);

        // update the position and return
        arena->position = new_position;
        return(ptr);
    }

    template<typename t>
    IFB_ENG_INTERNAL t*
    memory_arena_push_struct(
        memory_arena* const arena,
        const u32           count) {

        // check args
        memory_arena_validate(arena);
        assert(count != 0);

        // calculate the size
        const u32 size = (sizeof(t) * count);

        // do the push and return
        t* ptr = (t*)memory_arena_push(a, size);
        return(ptr);        
    }
};