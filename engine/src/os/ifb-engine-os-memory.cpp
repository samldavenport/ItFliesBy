#pragma once

#include "ifb-engine-os.hpp"

namespace ifb::eng {
    
    IFB_ENG_INTERNAL os_memory*
    os_memory_stack_alloc(
        stack& stack) {

        auto memory = stack.push_struct<os_memory>();
        assert(memory);

        memory->reservation_start = 0;
        memory->reservation_size  = 0;
        memory->committed_size    = 0;

        return(memory);
    }

    IFB_ENG_INTERNAL void
    os_memory_assert_valid(
        os_memory* memory) {

        assert(
            memory                    != NULL &&
            memory->reservation_start != NULL &&
            memory->reservation_size  != 0    &&
            memory->committed_size    <= memory->reservation_size
        );
    }

    IFB_ENG_INTERNAL void
    os_memory_virtual_reserve(
        os_memory* memory,
        const u64  size,
        const u64  alignment) {

        assert(memory != 0 && size != 0);

        const u64 alignment_pow_2 = size_round_up_pow2 (alignment);
        const u64 size_aligned    = size_align_pow_2   (size, alignment_pow_2)

        memory->reservation_size  = size_aligned;
        memory->reservation_start = (addr)os_memory_reserve(NULL, size_aligned);
        memory->committed_size    = 0;
        memory->alignment         = alignment_pow_2;

        os_memory_assert_valid(memory);
    }

    IFB_ENG_INTERNAL void
    os_memory_virtual_release(
        os_memory* memory) {

        os_memory_assert_valid(memory);

        const bool did_release = os_memory_release(
            memory->reservation_start,
            memory->reservation_size
        );

        assert(did_release);

        memory->reservation_start = 0;
        memory->reservation_size  = 0;
        memory->committed_size    = 0;
    }

    IFB_ENG_INTERNAL void*
    os_memory_virtual_commit(
        os_memory* memory,
        const u64  start,
        u64&       size) {

        os_memory_assert_valid(memory);

        void*     commit_start  = (void*)(memory->reservation_start + start);
        const u64 commit_size   = size_align_pow_2(size, memory->alignment);
        void*     commit_result = os_memory_commit(commit_start, commit_size);

        assert(commit_start == commit_result);

        memory->committed_size += commit_size;
        return(commit_result);
    }

    IFB_ENG_INTERNAL void
    os_memory_virtual_decommit(
        os_memory* memory,
        const u64  start,
        const u64  size) {
    
    }
};