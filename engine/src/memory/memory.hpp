#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "ifb-engine.hpp"

namespace ifb::eng {

    struct arena;

    IFB_ENG_INTERNAL arena* arena_alloc  (void);
    IFB_ENG_INTERNAL void   arena_free   (arena* const a);
    IFB_ENG_INTERNAL void   arena_reset  (arena* const a);
    IFB_ENG_INTERNAL u32    arena_save   (arena* const a);
    IFB_ENG_INTERNAL void   arena_revert (arena* const a, const u32 save);
    IFB_ENG_INTERNAL void   arena_revert (arena* const a);
    IFB_ENG_INTERNAL void*  arena_push   (arena* const a, const u32 size, const u32 alignment = 0);

    template<typename t>
    IFB_ENG_INTERNAL t* arena_push_struct(arena* const a, const u32 count = 1);

};

#endif //MEMORY_HPP