#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "ifb-engine.hpp"

namespace ifb::eng {

    struct memory_arena;

    constexpr u32 MEMORY_ARENA_SIZE = size_kilobytes(64);

    IFB_ENG_INTERNAL  memory_arena* memory_arena_alloc       (void);
    IFB_ENG_INTERNAL           void memory_arena_validate    (memory_arena* const arena);
    IFB_ENG_INTERNAL           void memory_arena_free        (memory_arena* const arena);
    IFB_ENG_INTERNAL           void memory_arena_reset       (memory_arena* const arena);
    IFB_ENG_INTERNAL            u32 memory_arena_save        (memory_arena* const arena);
    IFB_ENG_INTERNAL           void memory_arena_revert      (memory_arena* const arena, const u32 save);
    IFB_ENG_INTERNAL          void* memory_arena_push        (memory_arena* const arena, const u32 size, const u32 alignment = 0);
    IFB_ENG_INTERNAL_TEMPLATE(t) t* memory_arena_push_struct (memory_arena* const a, const u32 count = 1);
};

#endif //MEMORY_HPP