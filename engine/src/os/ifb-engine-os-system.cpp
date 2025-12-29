#pragma once

#include "ifb-engine-os.hpp"
#include "context.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    os_system_refresh_info(
        void) {

        os_manager* os_mngr = context_os_manager();

        assert(os_mngr);
        os_system_info* sys_info = os_mngr->system_info;

        // get system info
        os_system_get_cpu_info       (sys_info->cpu);
        os_system_get_memory_info    (sys_info->memory);
        os_system_get_cpu_cache_info (sys_info->cpu_cache_l1);
        os_system_get_cpu_cache_info (sys_info->cpu_cache_l2);
        os_system_get_cpu_cache_info (sys_info->cpu_cache_l3);
    }

    IFB_ENG_INTERNAL const os_system_memory_info&
    os_system_get_memory_info(
        void) {

        os_manager* os = context_os_manager();

        const os_system_info* sys = (os != NULL) ? os->system_info : NULL;
        assert(sys);

        const os_system_memory_info& mem = sys->memory;
        return(mem);
    }

    IFB_ENG_INTERNAL const os_system_cpu_info&
    os_system_get_cpu_info(
        void) {

        os_manager* os = context_os_manager();

        const os_system_info* sys = (os != NULL) ? os->system_info : NULL;
        assert(sys);

        const os_system_cpu_info& cpu = sys->cpu;
        return(cpu);
    }

    IFB_ENG_INTERNAL const os_system_cpu_cache_info&
    os_system_get_cpu_l1_cache_info(
        void) {

        os_manager* os = context_os_manager();

        const os_system_info* sys = (os != NULL) ? os->system_info : NULL;
        assert(sys);

        const os_system_cpu_cache_info& l1 = sys->cpu_cache_l1;
        return(l1);        
    }

    IFB_ENG_INTERNAL const os_system_cpu_cache_info&
    os_system_get_cpu_l2_cache_info(
        void) {

        os_manager* os = context_os_manager();

        const os_system_info* sys = (os != NULL) ? os->system_info : NULL;
        assert(sys);

        const os_system_cpu_cache_info& l2 = sys->cpu_cache_l2;
        return(l2);
    }

    IFB_ENG_INTERNAL const os_system_cpu_cache_info&
    os_system_get_cpu_l3_cache_info(
        void) {

        os_manager* os = context_os_manager();

        const os_system_info* sys = (os != NULL) ? os->system_info : NULL;
        assert(sys);


        const os_system_cpu_cache_info& l3 = sys->cpu_cache_l3;
        return(l3);
    }

};