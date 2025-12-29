#pragma once

#include "os-module.hpp"
#include "context.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    os_system_refresh_info(
        void) {

        os_system* sys = _os_module->system;

        // get system info
        os_system_get_cpu_info       (sys->cpu);
        os_system_get_memory_info    (sys->memory);
        os_system_get_cpu_cache_info (sys->cpu_cache_l1);
        os_system_get_cpu_cache_info (sys->cpu_cache_l2);
        os_system_get_cpu_cache_info (sys->cpu_cache_l3);
    }

    IFB_ENG_INTERNAL const os_system_memory_info&
    os_system_get_memory_info(
        void) {

        os_system* sys = _os_module->system;
        assert(sys);

        const os_system_memory_info& mem = sys->memory;
        return(mem);
    }

    IFB_ENG_INTERNAL const os_system_cpu_info&
    os_system_get_cpu_info(
        void) {

        os_system* sys = _os_module->system;
        assert(sys);

        const os_system_cpu_info& cpu = sys->cpu;
        return(cpu);
    }

    IFB_ENG_INTERNAL const os_system_cpu_cache_info&
    os_system_get_cpu_l1_cache_info(
        void) {

        os_system* sys = _os_module->system;
        assert(sys);

        const os_system_cpu_cache_info& l1 = sys->cpu_cache_l1;
        return(l1);        
    }

    IFB_ENG_INTERNAL const os_system_cpu_cache_info&
    os_system_get_cpu_l2_cache_info(
        void) {

        os_system* sys = _os_module->system;
        assert(sys); 

        const os_system_cpu_cache_info& l2 = sys->cpu_cache_l2;
        return(l2);
    }

    IFB_ENG_INTERNAL const os_system_cpu_cache_info&
    os_system_get_cpu_l3_cache_info(
        void) {

        os_system* sys = _os_module->system;
        assert(sys);

        const os_system_cpu_cache_info& l3 = sys->cpu_cache_l3;
        return(l3);
    }

};