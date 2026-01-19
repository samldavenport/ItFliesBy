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

        arena_allocator& arena_allocator = _map->os_reservation.arena_allocator; 
        const u32        arena_stride    = arena_allocator.arena_size;
        const u32        arena_count     = arena_allocator.arena_count;
        const addr       arena_region    = arena_allocator.start.as_addr; 
        arena*           arena_new       = NULL;

        for_count_u32(arena_index, arena_count) {

            const u32  arena_offset = (arena_stride * arena_index);
            const addr arena_addr   = (arena_region + arena_offset); 
            void*      arena_commit = (void*)arena_addr;
            const bool is_committed = os_memory_is_committed(arena_commit); 

            if(!is_committed) {

                arena_new = (arena*)sld::os_memory_commit(arena_commit, arena_stride);
                assert((void*)arena_new == arena_commit);

                ++_map->os_reservation.arena_allocator.arena_count;

                arena_new->position   = 0;
                arena_new->save       = 0;
                arena_new->prev       = NULL;
                arena_new->next       = arena_allocator.first;
                if ( arena_allocator.first) {
                    arena_allocator.first->prev = arena_new;
                }
                arena_allocator.first = arena_new;
                break;
            }
        }

        return(arena_new);
    }

    IFB_ENG_INTERNAL void
    arena_validate(
        arena* const a) {

        bool is_valid = (a != NULL);
        if (is_valid) {

            // get arena info
            const arena_allocator& arena_alctr = _map->os_reservation.arena_allocator;
            const u32              arena_stride = arena_alctr.arena_size;
            const addr             arena_min    = arena_alctr.start.as_addr;
            const addr             arena_max    = (arena_min + arena_alctr.size) - arena_stride;
            const addr             arena_start  = (addr)a;
            const addr             arena_offset = (arena_start - _map->os_reservation.start.as_addr);

            // ensure the arena is within the region
            // and aligned by granularity
            is_valid &= (arena_start  >= arena_min);
            is_valid &= (arena_start  <= arena_max);
            is_valid &= (arena_offset %  arena_stride == 0);
            is_valid &= (a->position  < MEMORY_ARENA_SIZE_ACTUAL);
            is_valid &= (a->save      <= a->position);
        }
        assert(is_valid);
    }

    IFB_ENG_INTERNAL void
    arena_free(
        arena* const a) {

        arena_validate(a);

        // remove from the list
        arena_allocator& arena_alctr = _map->os_reservation.arena_allocator;
        arena*           arena_next  = a->next;
        arena*           arena_prev  = a->prev;
        if (arena_next)         arena_next->prev  = arena_prev;
        if (arena_prev == NULL) arena_alctr.first = arena_next;
        else                    arena_prev->next  = arena_next;

        // decommit and adjust the count
        const bool did_decommit = sld::os_memory_decommit(
            (void*)a,
            arena_alctr.arena_size
        );
        assert(did_decommit);
        arena_alctr.arena_count--;
    }

    IFB_ENG_INTERNAL void
    arena_reset(
        arena* const a) {

        arena_validate(a);

        a->position = 0;
        a->save     = 0;
    }

    IFB_ENG_INTERNAL u32
    arena_save(
        arena* const a) {

        arena_validate(a);
        assert(a->save == 0);

        a->save = a->position;
        return(a->save);
    }

    IFB_ENG_INTERNAL void
    arena_revert(
        arena* const a,
        const u32    save) {

        arena_validate(a);
        assert(
            a->save == save &&
            a->save != 0    &&
            save    != 0
        );

        a->position = a->save;
        a->save     = 0;
    }

    IFB_ENG_INTERNAL void*
    arena_push(
        arena* const a,
        const u32           size,
        const u32           alignment) {

        // check args
        arena_validate(a);
        assert(size != 0);

        // align the size
        const u32 size_aligned = size_is_pow_2(alignment)
            ? size_align_pow_2 (size, alignment)
            : size_align       (size, alignment);

        // check if we can fit the push
        const u32  new_position = (a->position  + size_aligned);
        const bool can_push     = (new_position < MEMORY_ARENA_SIZE_ACTUAL); 
        if (!can_push) return(NULL);

        // calculate the pointer
        const addr start = (addr)a;
        void*      ptr   = (void*)(start + a->position);

        // update the position and return
        a->position = new_position;
        return(ptr);
    }

    template<typename t>
    IFB_ENG_INTERNAL t*
    arena_push_struct(
        arena* const a,
        const u32           count) {

        // check args
        arena_validate(a);
        assert(count != 0);

        // calculate the size
        const u32 size = (sizeof(t) * count);

        // do the push and return
        t* ptr = (t*)arena_push(a, size);
        return(ptr);        
    }
};