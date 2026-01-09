#pragma once

#include "memory.hpp"
#include "memory-map.cpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------


    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr u32 MEMORY_ARENA_SIZE_ACTUAL = (MEMORY_ARENA_SIZE - sizeof(arena));
    
    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL arena*
    arena_alloc(
        void) {

        assert(_map);

        const u32     arena_stride = _map->region.arenas.commit_granularity;
        const u32     arena_count  = _map->region.arenas.size / arena_stride;
        const addr    arena_region = _map->region.arenas.start.as_addr; 
        arena* arena        = NULL;

        for_count_u32(arena_index, arena_count) {

            const u32  arena_offset = (arena_stride * arena_index);
            const addr arena_addr   = (arena_region + arena_offset); 
            void*      arena_commit = (void*)arena_addr;
            const bool is_committed = os_memory_is_committed(arena_commit); 

            if(!is_committed) {

                arena = (arena*)sld::os_memory_commit(arena_commit, arena_stride);
                assert((void*)arena == arena_commit);

                ++_map->region.arenas.commit_count;

                arena->position   = 0;
                arena->save       = 0;
                arena->prev       = NULL;
                arena->next       = _arena_list.first;
                if (_arena_list.first) {
                    _arena_list.first->prev = arena;
                }
                _arena_list.first = arena;
                break;
            }
        }

        return(arena);
    }

    IFB_ENG_INTERNAL void
    arena_validate(
        arena* const arena) {

        bool is_valid = (arena != NULL);
        if (is_valid) {

            // get arena info
            const u32  arena_stride = _map->region.arenas.commit_granularity;
            const addr arena_min    = _map->region.arenas.start.as_addr;
            const addr arena_max    = (arena_min + _map->region.arenas.size) - arena_stride;
            const addr arena_start  = (addr)arena;
            const addr arena_offset = (arena_start - _map->os_reservation.start.as_addr);

            // ensure the arena is within the region
            // and aligned by granularity
            is_valid &= (arena_start     >= arena_min);
            is_valid &= (arena_start     <= arena_max);
            is_valid &= (arena_offset    %  arena_stride == 0);
            is_valid &= (arena->position < MEMORY_ARENA_SIZE_ACTUAL);
            is_valid &= (arena->save     <= arena->position);
        }
        assert(is_valid);
    }

    IFB_ENG_INTERNAL void
    arena_free(
        arena* const arena) {

        arena_validate(arena);

        // remove from the list
        arena* arena_next = arena->next;
        arena* arena_prev = arena->prev;
        if (arena_next)         arena_next->prev  = arena_prev;
        if (arena_prev == NULL) _arena_list.first = arena_next;
        else                    arena_prev->next  = arena_next;

        // decommit and adjust the count
        const bool did_decommit = sld::os_memory_decommit(
            (void*)arena,
            _map->region.arenas.commit_granularity
        );
        assert(did_decommit);
        _map->region.arenas.commit_count--;
    }

    IFB_ENG_INTERNAL void
    arena_reset(
        arena* const arena) {

        arena_validate(arena);

        arena->position = 0;
        arena->save     = 0;
    }

    IFB_ENG_INTERNAL u32
    arena_save(
        arena* const arena) {

        arena_validate(arena);
        assert(arena->save == 0);

        arena->save = arena->position;
        return(arena->save);
    }

    IFB_ENG_INTERNAL void
    arena_revert(
        arena* const arena,
        const u32           save) {

        arena_validate(arena);
        assert(
            arena->save == save &&
            arena->save != 0    &&
            save    != 0
        );

        arena->position = arena->save;
        arena->save     = 0;
    }

    IFB_ENG_INTERNAL void*
    arena_push(
        arena* const arena,
        const u32           size,
        const u32           alignment) {

        // check args
        arena_validate(arena);
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
    arena_push_struct(
        arena* const arena,
        const u32           count) {

        // check args
        arena_validate(arena);
        assert(count != 0);

        // calculate the size
        const u32 size = (sizeof(t) * count);

        // do the push and return
        t* ptr = (t*)arena_push(a, size);
        return(ptr);        
    }
};