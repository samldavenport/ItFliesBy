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

    file_t* file_mngr_get_file (const file_h32_t file_handle);
    void    file_mngr_startup  (void);
    
    struct file_t {
        file_error_s32_t        last_error;
        file_flags_u32_t        flags;
        file_t*                 next;
        file_t*                 prev;
        cchar*                  path;
        eng_mem_arena_t*        arena;
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