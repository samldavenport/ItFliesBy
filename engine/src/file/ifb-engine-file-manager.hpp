#ifndef IFB_ENGINE_FILE_MANAGER_HPP
#define IFB_ENGINE_FILE_MANAGER_HPP

#include <sld-os.hpp>

#ifndef    IFB_ENG_FILE_MANAGER_PATH_SIZE
#   define IFB_ENG_FILE_MANAGER_PATH_SIZE      256
#endif
#ifndef    IFB_ENG_FILE_MANAGER_TABLE_CAPACITY
#   define IFB_ENG_FILE_MANAGER_TABLE_CAPACITY 128
#endif

using namespace sld;

namespace ifb::eng {
  
    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr u32 FILE_MANAGER_TABLE_CAPACITY   = 64;
    constexpr u32 FILE_MANAGER_PATH_SIZE        = 256;
    constexpr u32 FILE_MANAGER_PATH_BUFFER_SIZE = FILE_MANAGER_PATH_SIZE * FILE_MANAGER_TABLE_CAPACITY;

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct file_mngr_t;
    struct file_os_async_callbacks_t;
    struct file_table_t;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void   file_mngr_startup       (void);
    IFB_ENG_INTERNAL void   file_mngr_shutdown      (void);
    IFB_ENG_INTERNAL file_t file_mngr_os_open_file  (const file_path_t path, const file_os_config_t& config);
    IFB_ENG_INTERNAL bool   file_mngr_os_close_file (const file_t file);
    IFB_ENG_INTERNAL bool   file_mngr_os_read       (const file_t file, file_os_buffer_t* file_buffer);
    IFB_ENG_INTERNAL bool   file_mngr_os_write      (const file_t file, file_os_buffer_t* file_buffer);
    IFB_ENG_INTERNAL u64    file_mngr_os_get_size   (const file_t file);

    IFB_ENG_INTERNAL_INLINE bool                           file_mngr_file_is_valid        (const file_t file);
    IFB_ENG_INTERNAL_INLINE const file_os_handle_t&        file_mngr_get_os_handle        (const file_t file);
    IFB_ENG_INTERNAL_INLINE const file_os_error_t&         file_mngr_get_os_error         (const file_t file);
    IFB_ENG_INTERNAL_INLINE const file_os_async_context_t& file_mngr_get_os_async_context (const file_t file);
    IFB_ENG_INTERNAL_INLINE const file_path_t&             file_mngr_get_path             (const file_t file);
    IFB_ENG_INTERNAL_INLINE const file_flags_t&            file_mngr_get_flags            (const file_t file);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct file_os_async_callbacks_t {
        file_os_async_callback_f read;
        file_os_async_callback_f write;
    };

    struct file_table_t {
        u64 capacity;
        struct {
            file_os_handle_t*        os_handle;
            file_os_error_t*         os_error;
            file_os_async_context_t* os_async;
            file_path_t*             path;
            file_flags_t*            flags;
        } array;
    };

    struct file_mngr_t {
        file_table_t              table;
        file_os_async_callbacks_t async_callbacks;        
    };

    //-------------------------------------------------------------------
    // GLOBALS
    //-------------------------------------------------------------------

    IFB_ENG_GLOBAL file_mngr_t      _mngr;
    IFB_ENG_GLOBAL file_os_handle_t _array_os_handle [FILE_MANAGER_TABLE_CAPACITY];
    IFB_ENG_GLOBAL file_os_error_t  _array_os_error  [FILE_MANAGER_TABLE_CAPACITY];  
    IFB_ENG_GLOBAL file_path_t      _array_path      [FILE_MANAGER_TABLE_CAPACITY];
    IFB_ENG_GLOBAL file_flags_t     _array_flags     [FILE_MANAGER_TABLE_CAPACITY];
    IFB_ENG_GLOBAL cchar            _path_buffer     [FILE_MANAGER_PATH_BUFFER_SIZE];

    //-------------------------------------------------------------------
    // INLINE
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL_INLINE bool
    file_mngr_file_is_valid(
        const file_t file) {

        return(file.index < _mngr.table.capacity);
    }

    IFB_ENG_INTERNAL_INLINE const file_os_handle_t&
    file_mngr_get_os_handle(
        const file_t file) {

        return(_mngr.table.array.os_handle[file.index]);
    }

    IFB_ENG_INTERNAL_INLINE const file_os_error_t&
    file_mngr_get_os_error(
        const file_t file) {

        return(_mngr.table.array.os_error[file.index]);
    }

    IFB_ENG_INTERNAL_INLINE const file_os_async_context_t&
    file_mngr_get_os_async_context(
        const file_t file) {

        return(_mngr.table.array.os_async[file.index]);
    }

    IFB_ENG_INTERNAL_INLINE const file_path_t&
    file_mngr_get_path(
        const file_t file) {

        return(_mngr.table.array.path[file.index]);
    }

    IFB_ENG_INTERNAL_INLINE const file_flags_t&
    file_mngr_get_flags(
        const file_t file) {

        return(_mngr.table.array.flags[file.index]);
    }
};

#endif //IFB_ENGINE_FILE_MANAGER_HPP