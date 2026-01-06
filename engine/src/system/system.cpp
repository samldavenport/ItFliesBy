#pragma once

#include "system.hpp"

namespace ifb::eng {
  
    static system_cpu_info       _cpu_info;
    static system_cpu_cache_info _cpu_cache_info;
    static system_memory_info    _memory_info;
    static system_cpu_cache_info _cpu_cache_info_l1;
    static system_cpu_cache_info _cpu_cache_info_l2;
    static system_cpu_cache_info _cpu_cache_info_l3;
    
    
    IFB_ENG_INTERNAL void
    system_refresh_info(
        void) {

        os_system_get_cpu_info       (_cpu_info);
        os_system_get_memory_info    (_memory_info);
        os_system_get_cpu_cache_info (_cpu_cache_info_l1);
        os_system_get_cpu_cache_info (_cpu_cache_info_l2);
        os_system_get_cpu_cache_info (_cpu_cache_info_l3);
    }

    IFB_ENG_INTERNAL const system_memory_info&
    system_get_memory_info(
        void) {

        return(_memory_info);
    }

    IFB_ENG_INTERNAL const system_cpu_info&
    system_get_cpu_info(
        void) {

        return(_cpu_info);
    }

    IFB_ENG_INTERNAL const system_cpu_cache_info&
    system_get_cpu_l1_cache_info(
        void) {

        return(_cpu_cache_info_l1);
    }

    IFB_ENG_INTERNAL const system_cpu_cache_info&
    system_get_cpu_l2_cache_info(
        void) {

        return(_cpu_cache_info_l2);
    }

    IFB_ENG_INTERNAL const system_cpu_cache_info&
    system_get_cpu_l3_cache_info(
        void) {

        return(_cpu_cache_info_l3);
    }    
};