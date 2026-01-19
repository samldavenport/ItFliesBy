#pragma once

#include "memory.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void*
    virtual_memory_commit(
        virtual_memory* const vmem,
        const u32             offset,
        const u32             size) {

        virtual_memory_validate(vmem);

        const u32 new_position = (vmem->position + size);
        return(NULL);
    }

    IFB_ENG_INTERNAL void
    virtual_memory_decommit(
        virtual_memory* const vmem,
        void*                 memory) {

    }

    IFB_ENG_INTERNAL void
    virtual_memory_validate(
        virtual_memory* const vmem) {

        bool is_valid = (vmem != NULL);
        if (is_valid) {
            is_valid &= (vmem->start.as_ptr != NULL);
            is_valid &= (vmem->size         != 0);
            is_valid &= (vmem->position     < vmem->size);
        }
        assert(is_valid);
    }
};