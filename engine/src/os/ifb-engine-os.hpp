#ifndef IFB_ENGINE_PLATFORM_MANAGER_HPP
#define IFB_ENGINE_PLATFORM_MANAGER_HPP

#include "ifb-engine.hpp"

#include <sld-os.hpp> 
#include <sld-stack.hpp> 
#include <sld-array-list.hpp>

namespace ifb::eng {


    constexpr u32 OS_MAX_COUNT_FILES    = IFB_ENG_CONFIG_OS_MAX_COUNT_FILES;
    constexpr u32 OS_MAX_COUNT_MONITORS = IFB_ENG_CONFIG_OS_MAX_COUNT_MONITORS;
    constexpr u32 OS_FILE_INVALID       = OS_MAX_COUNT_FILES; 
    constexpr u32 OS_MONITOR_INVALID    = OS_MAX_COUNT_MONITORS; 

    struct os_manager;
    struct os_memory;
    struct os_window;
    struct os_monitor_table;
    struct os_file_table;
    struct os_file;

    struct os_file    {u32 index; };
    struct os_monitor {u32 index; };
    struct os_file_list : array_list<os_file> { }; 

    struct os_monitor_table {
        u32                     count;
        os_monitor              primary; 
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
        addr reservation_start;
        u64  reservation_size;
        u64  committed_size;
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

    IFB_ENG_INTERNAL os_manager*       os_manager_stack_alloc       (stack& stack);
    IFB_ENG_INTERNAL void              os_manager_assert_valid      (const os_manager* mngr);
    IFB_ENG_INTERNAL void              os_manager_startup           (os_manager* mngr);
    IFB_ENG_INTERNAL void              os_manager_shutdown          (os_manager* mngr);

    IFB_ENG_INTERNAL os_memory*        os_memory_stack_alloc        (stack& stack);
    IFB_ENG_INTERNAL void              os_memory_reserve            (os_memory* memory, const u64 size);
    IFB_ENG_INTERNAL void              os_memory_release            (os_memory* memory);
    IFB_ENG_INTERNAL void              os_memory_assert_valid       (os_memory* memory);
    IFB_ENG_INTERNAL void*             os_memory_commit             (os_memory* memory, const u64 start, const u64 size);
    IFB_ENG_INTERNAL void              os_memory_decommit           (os_memory* memory, const u64 start, const u64 size);

    IFB_ENG_INTERNAL os_monitor_table* os_monitor_table_stack_alloc  (stack& stack);
    IFB_ENG_INTERNAL void              os_monitor_table_assert_valid (const os_monitor_table* monitor_table);
    IFB_ENG_INTERNAL void              os_monitor_table_refresh      (os_monitor_table* monitor_table);

    IFB_ENG_INTERNAL os_system_info*   os_system_info_stack_alloc   (stack& stack);
    IFB_ENG_INTERNAL void              os_system_info_assert_valid  (const os_system_info* system_info);
    IFB_ENG_INTERNAL void              os_system_info_refresh       (os_system_info* system_info);

    IFB_ENG_INTERNAL os_window*        os_window_stack_alloc        (stack& stack);
    IFB_ENG_INTERNAL void              os_window_assert_valid       (const os_window* window);

    IFB_ENG_INTERNAL os_file_table*    os_file_table_stack_alloc    (stack& stack);
    IFB_ENG_INTERNAL void              os_file_table_assert_valid   (const os_file_table* file_table);


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
    os_window_assert_valid(
        const os_window* window) {
    
        const bool is_valid = (
            window                    != NULL &&
            window->window_handle.val != NULL
        );
        assert(is_valid);
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