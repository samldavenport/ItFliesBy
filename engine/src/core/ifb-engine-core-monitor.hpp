#ifndef IFB_ENGINE_CORE_MONITOR_HPP
#define IFB_ENGINE_CORE_MONITOR_HPP

#include "ifb-engine.hpp"

namespace ifb::eng {
    
    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr u32 ENG_CORE_MONITOR_COUNT_MAX        = 16;
    constexpr u32 ENG_CORE_MONITOR_NAME_LENGTH      = sld::OS_MONITOR_NAME_WIDTH;
    constexpr u32 ENG_CORE_MONITOR_NAME_BUFFER_SIZE = (ENG_CORE_MONITOR_COUNT_MAX * sld::OS_MONITOR_NAME_WIDTH); 
    constexpr u32 ENG_CORE_MONITOR_INDEX_INVALID    = ENG_CORE_MONITOR_COUNT_MAX; 

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------

    struct core_monitor_name_t;
    struct core_monitor_table_t;
    struct core_monitor_info_t;

    using  core_monitor_os_handle_t = sld::os_monitor_handle_t;
    using  core_monitor_index_t     = u32_t;
    using  core_monitor_pos_t       = sld::dims_u32_pos_t;
    using  core_monitor_size_t      = sld::dims_u32_size_t;

    IFB_ENG_INTERNAL bool                            core_monitor_table_validate        (void);
    IFB_ENG_INTERNAL void                            core_monitor_table_assert_valid    (void);
    IFB_ENG_INTERNAL void                            core_monitor_table_init            (void);
    IFB_ENG_INTERNAL void                            core_monitor_table_refresh         (void);
    IFB_ENG_INTERNAL u32                             core_monitor_table_get_count       (void);
    IFB_ENG_INTERNAL const core_monitor_index_t      core_monitor_get_index_from_handle (const core_monitor_os_handle_t handle);
    IFB_ENG_INTERNAL const core_monitor_size_t&      core_monitor_get_primary_size      (void);
    IFB_ENG_INTERNAL const core_monitor_pos_t&       core_monitor_get_primary_position  (void);
    IFB_ENG_INTERNAL const core_monitor_name_t&      core_monitor_get_primary_name      (void);
    IFB_ENG_INTERNAL const core_monitor_os_handle_t& core_monitor_get_primary_handle    (void);
    IFB_ENG_INTERNAL const core_monitor_size_t&      core_monitor_get_size              (const core_monitor_index_t index);
    IFB_ENG_INTERNAL const core_monitor_pos_t&       core_monitor_get_position          (const core_monitor_index_t index);
    IFB_ENG_INTERNAL const core_monitor_name_t&      core_monitor_get_name              (const core_monitor_index_t index);
    IFB_ENG_INTERNAL const core_monitor_os_handle_t& core_monitor_get_handle            (const core_monitor_index_t index);

    struct core_monitor_name_t {
        cchar* buffer;
    };
    
    struct core_monitor_table_t {
        core_monitor_index_t monitor_primary;         
        core_monitor_index_t monitor_active;         
        core_monitor_size_t  monitor_virtual_size;
        u64                  monitor_count;
        struct {
            core_monitor_pos_t*       position;
            core_monitor_size_t*      size;
            core_monitor_name_t*      name;
            core_monitor_os_handle_t* handle;
        } array;
    };
};

#endif //IFB_ENGINE_CORE_MONITOR_HPP