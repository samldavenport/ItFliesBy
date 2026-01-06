#pragma once

#include "memory.hpp"

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

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr u32 MEMORY_ARENA_SIZE_ACTUAL = (MEMORY_ARENA_SIZE - sizeof(memory_arena));

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL memory_arena*
    memory_arena_alloc(
        void) {

        assert(false);
    }

    IFB_ENG_INTERNAL void
    memory_arena_validate(
        memory_arena* const arena) {

        bool is_valid = (arena != NULL);
        if (is_valid) {
            is_valid &= (arena->position < MEMORY_ARENA_SIZE_ACTUAL);
            is_valid &= (arena->save     < arena->position);
        }
        assert(is_valid);
    }

    IFB_ENG_INTERNAL void
    memory_arena_free(
        memory_arena* const arena) {

        assert(false);
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