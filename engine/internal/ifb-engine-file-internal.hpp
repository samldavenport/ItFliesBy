#pragma once

#include <sld-os.hpp>

#include "ifb-engine-file.hpp"
#include "ifb-engine-memory-internal.hpp"

namespace ifb {


    typedef sld::os_file_buffer_t           eng_file_os_buffer_t;
    typedef sld::os_file_async_callback_f   eng_file_os_async_callback_f;
    typedef sld::os_file_handle_t           eng_file_os_handle_t;
    typedef sld::os_file_error_t            eng_file_os_error_t;
    typedef sld::os_file_async_context_t    eng_file_os_async_context_t;
    typedef sld::os_file_os_context_t       eng_file_os_context_t;
    typedef sld::os_file_callback_context_t eng_file_callback_context_t;

    struct eng_file_t;
    struct eng_file_mngr_t;

    void        eng_file_mngr_startup  (void);
    eng_file_t* eng_file_mngr_get_file (const eng_file_h32_t file_handle);

    struct eng_file_t {
        eng_file_error_s32_t         last_error;
        eng_file_flags_u32_t         flags;
        eng_file_t*                  next;
        eng_file_t*                  prev;
        cchar*                       path;
        eng_mem_arena_t*             arena;
        eng_file_os_handle_t         os_handle;
        eng_file_os_async_context_t  os_async_context;
        u32                          index;
    };

    struct eng_file_mngr_t {
        eng_file_os_async_callback_f os_callback_read;
        eng_file_os_async_callback_f os_callback_write;
        u64                          buffer_size;
        u64                          capacity;
        u64                          path_size;
        struct {
            eng_file_t* opened;
            eng_file_t* closed;
        } list;
        eng_error_s32_t last_error;
    };
};