#pragma once

#include "memory.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    virtual_memory_acquire(
        virtual_memory*  const vmem,
        reserved_memory* const rmem,
        const u32              size) {

        // check args
        assert(
            vmem != NULL &&
            rmem != NULL &&
            size != 0
        );

        // align memory and check usage
        const u32 size_aligned      = memory_map_align_to_page(size);
        const u64 rmem_new_position = (rmem->position + size_aligned);
        assert(rmem_new_position < rmem->size);

        // intialize the vmem
        vmem->start.as_addr = rmem->start.as_addr + rmem->position;
        vmem->size          = size_aligned;
        vmem->rmem          = rmem;
        vmem->next          = NULL;

        // update the reserved position
        rmem->position = rmem_new_position;

        // if this is the first vmem,
        // set first and last node and return        
        if (rmem->vmem.first == NULL) {
            assert(rmem->vmem.last == NULL);

            rmem->vmem.first = vmem;
            rmem->vmem.last  = vmem;
            return;
        }

        // otherwise, add it to the end of the list
        virtual_memory* vmem_prev = rmem->vmem.last;
        assert(vmem_prev->next == NULL);
        vmem_prev->next = vmem;
        rmem->vmem.last = vmem;
    }

    IFB_ENG_INTERNAL void*
    virtual_memory_commit(
        virtual_memory* const vmem) {

    }

    IFB_ENG_INTERNAL void
    virtual_memory_decommit(
        virtual_memory* const vmem) {

    }

    IFB_ENG_INTERNAL void
    virtual_memory_validate(
        virtual_memory* const vmem) {

    }
};