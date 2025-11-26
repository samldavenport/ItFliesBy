#pragma once

#include "ifb-engine-os.hpp"

namespace ifb::eng {
    
    IFB_ENG_INTERNAL os_memory*
    os_memory_stack_alloc(
        stack& stack) {

    }

    IFB_ENG_INTERNAL void
    os_memory_reserve(
        os_memory* memory,
        const u64  size) {
            
    }
    IFB_ENG_INTERNAL void              os_memory_release            (os_memory* memory);
    IFB_ENG_INTERNAL void              os_memory_assert_valid       (os_memory* memory);
    IFB_ENG_INTERNAL void*             os_memory_commit             (os_memory* memory, const u64 start, const u64 size);
    IFB_ENG_INTERNAL void              os_memory_decommit           (os_memory* memory, const u64 start, const u64 size);

};