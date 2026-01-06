#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "ifb-engine.hpp"
#include <sld-os-system.hpp>

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using  system_memory_info    = os_system_memory_info;
    using  system_cpu_cache_info = os_system_cpu_cache_info;
    using  system_cpu_info       = os_system_cpu_info;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void                         system_refresh_info          (void);
    IFB_ENG_INTERNAL const system_memory_info&    system_get_memory_info       (void); 
    IFB_ENG_INTERNAL const system_cpu_info&       system_get_cpu_info          (void); 
    IFB_ENG_INTERNAL const system_cpu_cache_info& system_get_cpu_l1_cache_info (void); 
    IFB_ENG_INTERNAL const system_cpu_cache_info& system_get_cpu_l2_cache_info (void); 
    IFB_ENG_INTERNAL const system_cpu_cache_info& system_get_cpu_l3_cache_info (void); 
};

#endif //SYSTEM_HPP