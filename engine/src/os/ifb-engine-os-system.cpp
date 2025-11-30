#pragma once

#include "ifb-engine-os.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    os_system_info_assert_valid(
        const os_system_info* sys_info) {

        const bool is_valid = (
            sys_info                                != NULL &&
            sys_info->memory.allocation_granularity != 0    &&
            sys_info->memory.page_size              != 0    &&
            sys_info->memory.installed_ram_size_kb  != 0    &&
            sys_info->cpu.parent_core_number        != 0    &&
            sys_info->cpu.speed_mhz                 != 0    &&
            sys_info->cpu.core_count_physical       != 0    &&
            sys_info->cpu.core_count_logical        != 0    &&
            sys_info->cpu.cache_levels              != 0
        );
        assert(is_valid);
    }

    IFB_ENG_INTERNAL void
    os_manager_system_info_refresh(
        os_manager* os_mngr) {

        assert(os_mngr);
        os_system_info* sys_info = os_mngr->system_info;

        // get system info
        os_system_get_cpu_info       (sys_info->cpu);
        os_system_get_memory_info    (sys_info->memory);
        os_system_get_cpu_cache_info (sys_info->cpu_cache_l1);
        os_system_get_cpu_cache_info (sys_info->cpu_cache_l2);
        os_system_get_cpu_cache_info (sys_info->cpu_cache_l3);

        os_system_info_assert_valid(sys_info);
    }
};