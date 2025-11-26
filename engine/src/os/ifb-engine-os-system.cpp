#pragma once

#include "ifb-engine-os.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL os_system_info*
    os_system_info_stack_alloc(
        stack& stack) {

        os_system_info* system_info = stack.push_struct<os_system_info>();
        assert(system_info);
        return(system_info);
    }

    IFB_ENG_INTERNAL void
    os_system_info_assert_valid(
        const os_system_info* system_info) {

        const bool is_valid = (
            system_info                                != NULL &&
            system_info->memory.allocation_granularity != 0    &&
            system_info->memory.page_size              != 0    &&
            system_info->memory.installed_ram_size_kb  != 0    &&
            system_info->cpu.parent_core_number        != 0    &&
            system_info->cpu.speed_mhz                 != 0    &&
            system_info->cpu.core_count_physical       != 0    &&
            system_info->cpu.core_count_logical        != 0    &&
            system_info->cpu.cache_levels              != 0
        );
        assert(is_valid);
    }

    IFB_ENG_INTERNAL void
    os_system_info_refresh(
        os_system_info* system_info) {

        // get system info
        os_system_get_cpu_info       (system_info->cpu);
        os_system_get_memory_info    (system_info->memory);
        os_system_get_cpu_cache_info (system_info->cpu_cache_l1);
        os_system_get_cpu_cache_info (system_info->cpu_cache_l2);
        os_system_get_cpu_cache_info (system_info->cpu_cache_l3);
        os_system_info_assert_valid(system_info);
    }
};