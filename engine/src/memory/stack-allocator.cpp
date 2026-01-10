#pragma once

#include "memory.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    stack_memory_allocator_init(
        stack_allocator* const alctr,
        virtual_memory*  const vmem,
        const u32              size,
        const u32              granularity) {

        virtual_memory_validate(vmem);

        const u32 granularity_aligned = memory_map_align_to_page(granularity);
        const u32 size_aligned        = size_align_pow_2(size, granularity_aligned); 
        const u32 new_position        = (vmem->position + size_aligned); 

        bool can_init = true;
        can_init &= (alctr               != NULL);
        can_init &= (granularity_aligned != 0);
        can_init &= (size_aligned        != 0);
        can_init &= (size_aligned        >= granularity_aligned);
        can_init &= (new_position        < vmem->size);
        assert(can_init);

        alctr->vmem          = vmem;
        alctr->offset        = vmem->position;
        alctr->size          = size_aligned;
        alctr->granularity   = granularity_aligned;
        alctr->page_capacity = (size_aligned / granularity_aligned);
        alctr->page_count    = 0;
        alctr->page_position = 0;
    }

    IFB_ENG_INTERNAL void
    stack_memory_validate(
        stack_allocator* const alctr) {

        bool is_valid = (alctr != NULL);
        if (is_valid) {
            
            virtual_memory_validate(alctr->vmem);
            const virtual_memory* vmem = alctr->vmem;

            is_valid &= (alctr->offset        <  vmem->size);
            is_valid &= (alctr->size          != 0);
            is_valid &= (alctr->granularity   != 0);
            is_valid &= (alctr->page_capacity != 0);
            is_valid &= (alctr->page_count    <= alctr->page_capacity);
            is_valid &= (alctr->page_position <  alctr->granularity);
        }
        assert(is_valid);
    }

    IFB_ENG_INTERNAL void*
    stack_memory_alloc(
        stack_allocator* const alctr,
        const u32              size,
        const u32              alignment) {

        // check args
        stack_memory_validate(alctr);
        assert(size != 0);
        virtual_memory* vmem = alctr->vmem;

        // align the size
        const u32 size_aligned = size_is_pow_2(alignment)
            ? size_align_pow_2 (size, alignment)
            : size_align       (size, alignment);

        // calculate the new page position
        const u32 new_page_position = (size_aligned + alctr->page_position);

        // if we didn't exceed the page granularity, we're done
        if (new_page_position < alctr->granularity) {
            const u32  page_offset = (alctr->granularity * alctr->page_count);
            const addr page_start  = (vmem->start.as_addr + page_offset);
            const addr mem_start   = (page_start + alctr->page_position);
            void*      mem_ptr     = (void*)mem_start;
            c 
        }

        // make sure this allocation doesn't exceed the last page
        if (alctr->page_count == alctr->page_capacity) {
            assert( < alctr->granularity);
        }


    }

    IFB_ENG_INTERNAL_TEMPLATE(t) t*
    stack_memory_alloc_struct(
        stack_allocator* const alctr,
        const u32        count) {

    }

    IFB_ENG_INTERNAL void 
    stack_memory_free(
        stack_allocator* const alctr,
        void*            memory) {

    }

    IFB_ENG_INTERNAL void 
    stack_memory_reset(
        stack_allocator* const alctr,
        void*            memory) {

    }
};