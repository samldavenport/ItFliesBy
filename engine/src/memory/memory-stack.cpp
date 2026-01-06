#pragma once

#include "memory-map.cpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void*
    memory_stack_alloc(
        const u32 size,
        const u32 alignment) {

        assert(_map);

        void* mem = (void*)_map->stack.push(size, alignment);
        assert(mem);
        
        return(mem);
    }
    
    IFB_ENG_INTERNAL_TEMPLATE(t) t*
    memory_stack_alloc_struct(
        const u32 count) {

        assert(_map);

        t* mem = _map->stack.push_struct<t>(count);
        assert(mem);
        
        return(mem);
    }

    IFB_ENG_INTERNAL void
    memory_stack_get_info(
        memory_stack_info& info) {

        assert(_map);
        info.size_total = _map->stack.capacity;
        info.size_used  = _map->stack.position; 
    }
};