#ifndef IFB_ENG_CORE_BLOCK_ALLOCATOR_HPP
#define IFB_ENG_CORE_BLOCK_ALLOCATOR_HPP

#include "ifb-engine.hpp"
#include "memory.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    block_memory_allocator_init(
        block_allocator* const alctr,
        virtual_memory*  const vmem,
        const u32              size_total,
        const u32              block_size) {

    }

    IFB_ENG_INTERNAL void*
    block_memory_alloc(
        block_allocator* const alctr) {

    }

    IFB_ENG_INTERNAL void
    block_memory_free(
        block_allocator* const alctr,
        void*                  block) {

    }

    IFB_ENG_INTERNAL void
    block_memory_reset(
        block_allocator* const alctr,
        void*                  block) {

    }
};

#endif //IFB_ENG_CORE_BLOCK_ALLOCATOR_HPP