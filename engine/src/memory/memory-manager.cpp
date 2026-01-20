#pragma once

#include "memory.hpp"
#include "system.hpp"
#include <sld-stack.hpp>
#include <sld-os-memory.hpp>

namespace ifb::eng {

    void
    memory_manager::startup(
        void) {

    }

    void
    memory_manager::shutdown(
        void) {

    }

    arena*
    memory_manager::arena_alloc(
        void) {

        auto alctr = _arena_allocator;
        assert(alctr != NULL);
        alctr->ggvalidate();

        const bool can_alloc = (alctr->arena_count_used < alctr->arena_count_total);
        if (!can_alloc) return(NULL);


        arena* a = NULL;

        for_count_u32(
            arena_index,
            alctr->arena_count_total) {

            const u32  offset      = _arena_allocator->arena_size * arena_index; 
            const addr arena_start = _arena_allocator->start + offset);
        
            if (os_memory_is_reserved((void*)arena_start)) {

                a = (arena*)arena_start;
                a->index    = arena_index;
                a->position = 0;
                a->save     = 0;

                break;
            }
        }



    }

    void   memory_manager::arena_free              (arena** arena);
    void*  memory_manager::virtual_memory_commit   (virtual_memory* const vmem, const u32 offset, const u32 size);
    void   memory_manager::virtual_memory_decommit (virtual_memory* const vmem, const u32 offset, const u32 size);
    
    template<typename t> t*
    memory_manager::singleton_alloc(
        const u32 count) {

        assert(count != 0);
        
        t* mem = _mem_map->singleton_stack.push_struct<t>(count);
        assert(mem);
        return(mem);    
    }

    //-------------------------------------------------------------------
    // GLOBALS
    //-------------------------------------------------------------------

    static memory_map* _map;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void
    memory_map_set(
        memory_map* const mem_map) {

        bool is_valid = (mem_map != NULL);
        if (is_valid) {
            is_valid &= mem_map->singleton_stack.is_valid();
            is_valid &= mem_map->os_virtual_memory.granularity != 0;
            is_valid &= mem_map->os_virtual_memory.page_size   != 0;
            is_valid &= mem_map->os_virtual_memory.reservation.arenas.is_valid();
            is_valid &= mem_map->os_virtual_memory.reservation.entities.is_valid();
            is_valid &= mem_map->os_virtual_memory.reservation.graphics.is_valid();
        }
        assert(is_valid);

        _map = mem_map;
    }

    IFB_ENG_INTERNAL void
    memory_map_destroy(
        void) {

    }

    IFB_ENG_INTERNAL u32
    memory_map_align_to_page(
        const u32 size) {

        assert(size != 0 && _map->os_virtual_memory.page_size != 0);

        const u32 size_aligned = size_align_pow_2(size, _map->os_virtual_memory.page_size);
        return(size_aligned);
    }

    IFB_ENG_INTERNAL u32
    memory_map_align_to_granularity(
        const u32 size) {

        assert(size != 0 && _map->os_virtual_memory.granularity != 0);

        const u32 size_aligned = size_align_pow_2(size, _map->os_virtual_memory.granularity);
        return(size_aligned);
    }
};