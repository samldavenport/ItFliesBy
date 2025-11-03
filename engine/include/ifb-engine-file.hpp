#ifndef IFB_ENG_FILE_HPP
#define IFB_ENG_FILE_HPP

#include "ifb-engine.hpp"
#include <sld-os.hpp>

#define IFB_ENG_FILE_INVALID_INDEX 0xFFFFFFFF

using namespace sld;

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using  file_error_t               = s32_t;
    using  file_flags_t               = u32_t;
    using  file_os_buffer_t           = os_file_buffer_t;
    using  file_os_async_callback_f   = os_file_async_callback_f;
    using  file_os_handle_t           = os_file_handle_t;
    using  file_os_error_t            = os_file_error_t;
    using  file_os_async_context_t    = os_file_async_context_t; 
    using  file_os_context_t          = os_file_os_context_t;
    using  file_os_callback_context_t = os_file_callback_context_t;
    using  file_os_config_t           = os_file_config_t; 
    struct file_t;
    struct file_path_t;
    struct file_info_t;

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum file_flag_ {
        file_flag_none        = 0,
        file_flag_error       = bit_value(0),
        file_flag_internal    = bit_value(1),
        file_flag_ro          = bit_value(2),
        file_flag_rw          = bit_value(3),
        file_flag_io_pending  = bit_value(4),
        file_flag_io_complete = bit_value(5),
        file_flag_read        = bit_value(6),
        file_flag_write       = bit_value(7)
    };

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_API const file_t       file_open_ro_new            (const file_path_t path);
    IFB_ENG_API const file_t       file_open_ro_existing       (const file_path_t path);
    IFB_ENG_API const file_t       file_open_ro_always         (const file_path_t path);
    IFB_ENG_API const file_t       file_open_ro_overwrite      (const file_path_t path);
    IFB_ENG_API const file_t       file_open_rw_new            (const file_path_t path);
    IFB_ENG_API const file_t       file_open_rw_existing       (const file_path_t path);
    IFB_ENG_API const file_t       file_open_rw_always         (const file_path_t path);
    IFB_ENG_API const file_t       file_open_rw_overwrite      (const file_path_t path);
    IFB_ENG_API bool               file_close                  (const file_t file);
    IFB_ENG_API void               file_reset                  (const file_t file);
    IFB_ENG_API u64                file_get_size               (const file_t file);
    IFB_ENG_API const file_path_t  file_get_path               (const file_t file); 
    IFB_ENG_API const file_error_t file_get_error              (const file_t file);
    IFB_ENG_API const file_flags_t file_get_flags              (const file_t file);
    IFB_ENG_API void               file_get_info               (const file_t file, file_info_t*      info);
    IFB_ENG_API bool               file_read                   (const file_t file, file_os_buffer_t* buffer);
    IFB_ENG_API bool               file_write                  (const file_t file, file_os_buffer_t* buffer);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct file_t {
        u32 index;
    };

    struct file_path_t {
        cchar* buffer;
    };
    
    struct file_info_t {
        file_path_t   path;
        file_flags_t  flags;
        file_error_t  error;
        u64           size;
    };

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

};

#endif  //IFB_ENGINE_FILE_HPP