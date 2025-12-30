#pragma once

#include "os-module.cpp"

namespace ifb::eng {

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
    os_memory_reserve(
        void) {

        os_memory* os_mem = _os_module->memory;
        os_system* os_sys = _os_module->system;
        
        const u64 memory_size_installed = size_kilobytes(os_sys->memory.installed_ram_size_kb);

        os_mem->reservation_size  = (memory_size_installed / 2);
        os_mem->reservation_start = (addr)sld::os_memory_reserve(NULL, os_mem->reservation_size);
        os_mem->alignment         = os_sys->memory.page_size;  
        os_mem->committed_size    = 0;

        os_memory_assert_valid(os_mem);
    }

    IFB_ENG_INTERNAL void
    os_memory_release(
        void) {

        os_memory* os_mem = _os_module->memory;
        os_memory_assert_valid(os_mem);

        const bool did_release = sld::os_memory_release(
            (void*)os_mem->reservation_start,
            os_mem->reservation_size
        );
        assert(did_release);

        os_mem->reservation_size  = 0;
        os_mem->reservation_start = 0;
        os_mem->alignment         = 0;
        os_mem->committed_size    = 0;
    }

    IFB_ENG_INTERNAL void*
    os_memory_commit(
        const u64 offset,
        const u64 size) {

        os_memory*  os_mem  = _os_module->memory;
        os_memory_assert_valid(os_mem);

        const u64  commit_size     = size_align_pow_2(size, os_mem->alignment);
        void*      commit_start    = (void*)(os_mem->reservation_start + offset); 
        const bool is_aligned      = (offset % os_mem->alignment == 0); 
        const bool is_reserved     = os_memory_is_reserved(commit_start); 
        void*      commit_result   = sld::os_memory_commit(commit_start, commit_size);

        os_mem->committed_size += commit_size;

        assert(
            is_reserved                                                                             &&
            os_mem->committed_size <= os_mem->reservation_size                                      &&
            commit_size            != 0                                                             &&
            commit_start           >= (void*)os_mem->reservation_start                              &&
            commit_start           <= (void*)(os_mem->reservation_start + os_mem->reservation_size) &&
            commit_result          == commit_start
        );

        return(commit_result);
    }

    IFB_ENG_INTERNAL void
    os_memory_decommit(
        void*       start,
        const u64   size) {

        os_memory* os_mem = _os_module->memory;
        os_memory_assert_valid(os_mem);

        const bool is_aligned   = (((addr)start) % os_mem->alignment == 0);
        const u64  commit_size  = size_align_pow_2(size, os_mem->alignment);
        const bool is_committed = sld::os_memory_is_committed (start);
        const bool did_decommit = sld::os_memory_decommit     (start, commit_size);
        const bool can_decommit = (os_mem->committed_size >= commit_size);

        os_mem->committed_size -= commit_size;

        assert(
            is_aligned   &&
            did_decommit && 
            can_decommit && 
            is_committed && 
            commit_size  != 0 
        );
    }

    IFB_ENG_INTERNAL bool
    os_memory_is_page_aligned(
        const u64 start) {

        os_memory* os_mem = _os_module->memory;
        os_memory_assert_valid(os_mem);

        const bool is_aligned = (start % os_mem->alignment == 0);
        return(is_aligned);
    }

    IFB_ENG_INTERNAL void
    os_memory_check_usage(
        void) {

        os_memory* os_mem = _os_module->memory;
        os_memory_assert_valid(os_mem);

        assert(
            os_mem != NULL &&
            os_mem->reservation_start != 0 &&
            os_mem->reservation_size  != 0 &&
            os_mem->committed_size    <= os_mem->reservation_size
        );
    }

    IFB_ENG_INTERNAL const addr
    os_memory_get_reservation_start(
        void) {

        os_memory* os_mem = _os_module->memory;
        os_memory_assert_valid(os_mem);

        return(os_mem->reservation_start);
    }
};