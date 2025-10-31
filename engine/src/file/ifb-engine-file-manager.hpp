#ifndef IFB_ENGINE_FILE_MANAGER_HPP
#define IFB_ENGINE_FILE_MANAGER_HPP

#include <sld-os.hpp>

#ifndef    IFB_ENG_FILE_MANAGER_PATH_SIZE
#   define IFB_ENG_FILE_MANAGER_PATH_SIZE      256
#endif
#ifndef    IFB_ENG_FILE_MANAGER_TABLE_CAPACITY
#   define IFB_ENG_FILE_MANAGER_TABLE_CAPACITY 128
#endif

namespace ifb::eng {

    constexpr u32 FILE_MANAGER_PATH_SIZE        = 256;
    constexpr u32 FILE_MANAGER_TABLE_CAPACITY   = 128;
    constexpr u32 FILE_MANAGER_PATH_BUFFER_SIZE = FILE_MANAGER_PATH_SIZE * FILE_MANAGER_TABLE_CAPACITY;
    constexpr u32 FILE_MANAGER_INVALID_HANDLE   = IFB_ENG_FILE_INVALID_HANDLE; 

    using  file_os_buffer_t            = sld::os_file_buffer_t;
    using  file_os_async_callback_f    = sld::os_file_async_callback_f;
    using  file_os_handle_t            = sld::os_file_handle_t;
    using  file_os_error_t             = sld::os_file_error_t;
    using  file_os_async_context_t     = sld::os_file_async_context_t; 
    using  file_os_context_t           = sld::os_file_os_context_t;
    using  file_os_callback_context_t  = sld::os_file_callback_context_t;
    struct file_t;
    struct file_mngr_t;

    IFB_ENG_INTERNAL void          file_mngr_startup              (void);
    IFB_ENG_INTERNAL void          file_mngr_shutdown             (void);
    IFB_ENG_INTERNAL file_handle_t file_mngr_get_next_free_handle (void);
    IFB_ENG_INTERNAL file_handle_t file_mngr_os_open_file         (const cchar* path, const sld::os_file_config_t& config);

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
        } array;
    };

    struct file_mngr_t {
        file_table_t              table;
        file_os_async_callbacks_t async_callbacks;        
    };
};

#endif //IFB_ENGINE_FILE_MANAGER_HPP