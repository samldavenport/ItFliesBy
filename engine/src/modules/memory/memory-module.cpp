#pragma once

#include "memory-module.hpp"
#include "context.hpp"

namespace ifb::eng {

    static memory_module* _mem;

    IFB_ENG_INTERNAL memory_module*
    memory_module_init(
        void) {

        _mem = context_stack_alloc<memory_module>();
        assert(_mem);
        return(_mem);
    }

    IFB_ENG_INTERNAL void
    memory_module_startup(
        void) {

        _mem->map.os_resources.size_total = MEMORY_MAP_SIZE_OS_RESOURCES;
        _mem->map.os_resources.start      = MEMORY_MAP_OFFSET_OS_RESOURCES;
        _mem->map.graphics.size_total     = MEMORY_MAP_SIZE_GRAPHICS;
        _mem->map.graphics.start          = MEMORY_MAP_OFFSET_GRAPHICS;
    } 

    IFB_ENG_INTERNAL void
    memory_module_shutdown(
        void) {

    }
};