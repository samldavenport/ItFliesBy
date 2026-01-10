#pragma once

#include "memory.hpp"
#include "system.hpp"
#include <sld-stack.hpp>
#include <sld-os-memory.hpp>

namespace ifb::eng {

    //-------------------------------------------------------------------
    // GLOBALS
    //-------------------------------------------------------------------

    static byte        _stack_memory[MEMORY_STACK_SIZE];
    static memory_map* _map;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL memory_map*
    memory_map_create(
        void) {

        // initialize the stack and allocate map
        stack mem_stack(_stack_memory, MEMORY_STACK_SIZE);

        // get the memory info and reserve memory
        const system_memory_info& mem_info      = system_get_memory_info();
        const u64                 mem_installed = size_kilobytes(mem_info.installed_ram_size_kb);
        const u64                 mem_res_size  = (mem_installed / 2);
        const addr                mem_res_start = (addr)sld::os_memory_reserve(NULL, mem_res_size);
        assert(mem_res_start);

        // calculate addresses of regions
        const addr region_start_arenas   = (mem_res_start + MEMORY_REGION_OFFSET_ARENAS);
        const addr region_start_entities = (mem_res_start + MEMORY_REGION_OFFSET_ENTITIES);
        const addr region_start_graphics = (mem_res_start + MEMORY_REGION_OFFSET_GRAPHICS);

        // allocate and initialize map
        _map = mem_stack.push_struct<memory_map>();
        assert(_map);
        _map->singleton_stack.init(mem_stack.data, mem_stack.capacity);
        _map->os_reservation.start.as_addr       = mem_res_start;
        _map->os_reservation.size                = mem_res_size;
        _map->os_reservation.granularity         = mem_info.allocation_granularity;
        _map->os_reservation.page_size           = mem_info.page_size;
        return(_map);
    }

    IFB_ENG_INTERNAL void
    memory_map_destroy(
        void) {

    }

    IFB_ENG_INTERNAL u32
    memory_map_align_to_page(
        const u32 size) {

        assert(size != 0 && _map->os_reservation.page_size != 0);

        const u32 size_aligned = size_align_pow_2(size, _map->os_reservation.page_size);
        return(size_aligned);
    }

    IFB_ENG_INTERNAL u32
    memory_map_align_to_granularity(
        const u32 size) {

        assert(size != 0 && _map->os_reservation.granularity != 0);

        const u32 size_aligned = size_align_pow_2(size, _map->os_reservation.granularity);
        return(size_aligned);
    }
};