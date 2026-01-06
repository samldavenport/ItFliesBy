#pragma once

#include "memory.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct arena {
        arena* next;
        arena* prev;
        u32    position;
        u32    save;
    };

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

        assert(false);
    }

    IFB_ENG_INTERNAL void
    arena_validate(
        arena* const a) {

        bool is_valid = (a != NULL);
        if (is_valid) {
            is_valid &= (a->position < MEMORY_ARENA_SIZE_ACTUAL);
            is_valid &= (a->save     < a->position);
        }
        assert(is_valid);
    }

    IFB_ENG_INTERNAL void
    arena_free(
        arena* const a) {

        assert(false);
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
        const u32    size,
        const u32    alignment) {

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
        const u32    count) {

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