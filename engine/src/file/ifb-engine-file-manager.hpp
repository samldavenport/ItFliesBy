#ifndef IFB_ENGINE_FILE_MANAGER_HPP
#define IFB_ENGINE_FILE_MANAGER_HPP

#include <sld-os.hpp>

namespace ifb::eng {


    using  file_os_buffer_t         = sld::os_file_buffer_t;
    using  file_os_async_callback_f = sld::os_file_async_callback_f;
    using  file_os_handle_t         = sld::os_file_handle_t;
    using  file_os_error_t          = sld::os_file_error_t;
    using  file_os_async_context_t  = sld::os_file_async_context_t;
    using  file_os_context_t        = sld::os_file_os_context_t;
    using  file_callback_context_t  = sld::os_file_callback_context_t;
    struct file_t;
    struct file_mngr_t;

    IFB_ENG_INTERNAL void    file_mngr_startup               (void);
    IFB_ENG_INTERNAL void    file_mngr_shutdown              (void);
    IFB_ENG_INTERNAL file_t* file_mngr_get_file              (const file_h32_t file_handle);
    IFB_ENG_INTERNAL file_t* file_mngr_open_ro               (const cchar*      file_path);
    IFB_ENG_INTERNAL file_t* file_mngr_open_rw               (const cchar*      file_path);
    IFB_ENG_INTERNAL bool    file_mngr_close                 (const file_h32_t  file_handle);
    IFB_ENG_INTERNAL bool    file_mngr_read                  (const file_h32_t  file_handle, file_buffer_t& read_buffer);
    IFB_ENG_INTERNAL bool    file_mngr_write                 (const file_h32_t  file_handle, file_buffer_t& write_buffer);
    IFB_ENG_INTERNAL bool    file_mngr_read_async            (const file_h32_t  file_handle);
    IFB_ENG_INTERNAL bool    file_mngr_write_async           (const file_h32_t  file_handle);
    
    struct file_t {
        file_error_s32_t        last_error;
        file_flags_u32_t        flags;
        file_t*                 next;
        file_t*                 prev;
        cchar*                  path;
        file_os_handle_t        os_handle;
        file_os_async_context_t os_async_context;
        u32                     index;
    };

    struct file_mngr_t {
        file_os_async_callback_f os_callback_read;
        file_os_async_callback_f os_callback_write;
        u64                      buffer_size;
        u64                      capacity;
        u64                      path_size;
        struct {
            file_t* opened;
            file_t* closed;
        } list;
        eng_error_s32_t last_error;
    };
};

#endif //IFB_ENGINE_FILE_MANAGER_HPP