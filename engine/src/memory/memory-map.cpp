#pragma once

#include "memory.hpp"
#include "system.hpp"
#include <sld-stack.hpp>
#include <sld-os-memory.hpp>

namespace ifb::eng {

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct memory_reservation : memory {
        u32 granularity;
        u32 page_size;
    };

    struct memory_region : memory {
        u32 commit_granularity;
        u32 commit_count;
    };

    struct memory_map {
        stack              stack;
        memory_reservation os_reservation;
        struct {
            memory_region arenas;
            memory_region graphics;
            memory_region entities;
        } region;
    };

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
        const addr region_start_arenas   = mem_res_start + MEMORY_REGION_OFFSET_ARENAS;
        const addr region_start_entities = mem_res_start + MEMORY_REGION_OFFSET_ENTITIES;
        const addr region_start_graphics = mem_res_start + MEMORY_REGION_OFFSET_GRAPHICS;

        // allocate and initialize map
        _map = mem_stack.push_struct<memory_map>();
        assert(_map);
        _map->stack                              = mem_stack;
        _map->os_reservation.as_addr             = mem_res_start;
        _map->os_reservation.size                = mem_res_size;
        _map->os_reservation.granularity         = mem_info.allocation_granularity;
        _map->os_reservation.page_size           = mem_info.page_size;
        _map->region.arenas.as_addr              = region_start_arenas;
        _map->region.arenas.size                 = MEMORY_REGION_SIZE_ARENAS;  
        _map->region.arenas.commit_granularity   = MEMORY_REGION_GRANULARITY_ARENAS;  
        _map->region.arenas.commit_count         = 0;  
        _map->region.entities.as_addr            = region_start_entities;
        _map->region.entities.size               = MEMORY_REGION_SIZE_ENTITIES;
        _map->region.entities.commit_granularity = MEMORY_REGION_GRANULARITY_ENTITIES;  
        _map->region.entities.commit_count       = 0;  
        _map->region.graphics.as_addr            = region_start_graphics;
        _map->region.graphics.size               = MEMORY_REGION_SIZE_GRAPHICS;
        _map->region.graphics.commit_granularity = MEMORY_REGION_GRANULARITY_GRAPHICS;
        _map->region.graphics.commit_count       = 0;  
        return(_map);
    }

    IFB_ENG_INTERNAL void
    memory_map_destroy(
        void) {

    }
};