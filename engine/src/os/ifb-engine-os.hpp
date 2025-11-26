#ifndef IFB_ENGINE_PLATFORM_MANAGER_HPP
#define IFB_ENGINE_PLATFORM_MANAGER_HPP

#include "ifb-engine.hpp"

#include <sld-os.hpp> 
#include <sld-stack.hpp> 
#include <sld-array-list.hpp>

namespace ifb::eng {


    constexpr u32 OS_MAX_COUNT_MONITORS = IFB_ENG_CONFIG_OS_MAX_COUNT_MONITORS;
    constexpr u32 OS_MAX_COUNT_FILES    = IFB_ENG_CONFIG_OS_MAX_COUNT_FILES;

    struct os_manager;
    struct os_memory;
    struct os_window;
    struct os_monitor_table;
    struct os_file_table;
    struct os_file;

    struct os_file { u32 index; };
    struct os_file_list : array_list<os_file> { }; 

    struct os_monitor_table {
        u32                     count;
        os_monitor_handle       primary_handle; 
        os_monitor_working_area working_area;
        struct {
            os_monitor_handle*      handles;
            os_monitor_dimensions*  dimensions;
            os_monitor_name*        names;
        } array;
    };

    struct os_window {
        os_window_handle window_handle;
    };

    struct os_file_table {
        os_file_handle* handle_array;
        os_file_list    file_list_open;
        os_file_list    file_list_closed;
    };

    struct os_memory {
        void* reservation_start;
        u64   reservation_size;
        u64   committed_size;
    };

    struct os_system_info {
        os_system_memory_info    memory;
        os_system_cpu_info       cpu;
        os_system_cpu_cache_info cpu_cache_l1;
        os_system_cpu_cache_info cpu_cache_l2;
        os_system_cpu_cache_info cpu_cache_l3;
    };

    struct os_manager {
        os_system_info*   system_info;
        os_window*        window;
        os_monitor_table* monitor_table;
        os_file_table*    file_table;
        os_memory*        memory;
    };

    IFB_ENG_INTERNAL os_manager* os_manager_stack_alloc  (stack& stack);
    IFB_ENG_INTERNAL void        os_manager_startup      (os_manager* mngr);
    IFB_ENG_INTERNAL void        os_manager_shutdown     (os_manager* mngr);


    IFB_ENG_INTERNAL_INLINE void os_manager_assert_valid       (const os_manager*       mngr);
    IFB_ENG_INTERNAL_INLINE void os_system_info_assert_valid   (const os_system_info*   system_info);
    IFB_ENG_INTERNAL_INLINE void os_window_assert_valid        (const os_window*        window);
    IFB_ENG_INTERNAL_INLINE void os_monitor_table_assert_valid (const os_monitor_table* monitor_table);
    IFB_ENG_INTERNAL_INLINE void os_file_table_assert_valid    (const os_file_table*    file_table);
    IFB_ENG_INTERNAL_INLINE void os_memory_assert_valid        (const os_memory*        memory);


    IFB_ENG_INTERNAL_INLINE void
    os_manager_assert_valid(
        const os_manager* mngr) {
    
        const bool is_valid = (
            mngr                != NULL &&
            mngr->system_info   != NULL &&
            mngr->window        != NULL &&
            mngr->monitor_table != NULL &&
            mngr->file_table    != NULL
        );
        assert(is_valid);
    }

    IFB_ENG_INTERNAL_INLINE void
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

    IFB_ENG_INTERNAL_INLINE void
    os_window_assert_valid(
        const os_window* window) {
    
        const bool is_valid = (
            window                    != NULL &&
            window->window_handle.val != NULL
        );
        assert(is_valid);
    }

    IFB_ENG_INTERNAL_INLINE void
    os_monitor_table_assert_valid(
        const os_monitor_table* monitor_table) {

        
    }

    IFB_ENG_INTERNAL_INLINE void
    os_file_table_assert_valid(
        const os_file_table* file_table) {
    
    }

    IFB_ENG_INTERNAL_INLINE void
    os_memory_assert_valid(
        const os_memory* memory) {

        const bool is_valid = (
            memory                    != NULL &&
            memory->reservation_size  != 0    &&
            memory->reservation_start != NULL &&
            memory->committed_size    <= memory->reservation_size
        );
        assert(is_valid);
    }
};

#endif //IFB_ENGINE_PLATFORM_MANAGER_HPP