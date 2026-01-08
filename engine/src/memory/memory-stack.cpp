#pragma once

#include "memory-map.cpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void*
    singleton_stack_alloc(
        const u32 size,
        const u32 alignment) {

        assert(_map);

        void* mem = (void*)_map->singleton_stack.push(size, alignment);
        assert(mem);
        
        return(mem);
    }
    
    IFB_ENG_INTERNAL_TEMPLATE(t) t*
    singleton_stack_alloc_struct(
        const u32 count) {

        assert(_map);

        t* mem = _map->singleton_stack.push_struct<t>(count);
        assert(mem);
        
        return(mem);
    }

    IFB_ENG_INTERNAL void
    singleton_stack_get_info(
        singleton_stack_info& info) {

        assert(_map);
        info.size_total = _map->singleton_stack.capacity;
        info.size_used  = _map->singleton_stack.position; 
    }
};