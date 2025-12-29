#pragma once

#include "memory.hpp"
#include "context.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    memory_manager_startup(
        void) {

        memory_manager* mngr = context_get_memory_manager();

        mngr->map.os_resources.size_total = MEMORY_MAP_SIZE_OS_RESOURCES;
        mngr->map.os_resources.start      = MEMORY_MAP_OFFSET_OS_RESOURCES;

        mngr->map.graphics.size_total     = MEMORY_MAP_SIZE_GRAPHICS;
        mngr->map.graphics.start          = MEMORY_MAP_OFFSET_GRAPHICS;

    } 

    IFB_ENG_INTERNAL void
    memory_manager_shutdown(
        void) {

    }
};