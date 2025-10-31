#ifndef IFB_ENG_FILE_HPP
#define IFB_ENG_FILE_HPP

#include "ifb-engine.hpp"
#include <sld-os.hpp>

#define IFB_ENG_FILE_INVALID_HANDLE 0xFFFFFFFF

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using  file_error_t  = s32_t;
    using  file_handle_t = h32_t;
    using  file_flags_t  = u32_t;
    struct file_buffer_t;
    struct file_path_t;
    struct file_t;

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum file_flag_ {
        file_flag_none        = 0,
        file_flag_error       = sld::bit_value(0),
        file_flag_internal    = sld::bit_value(1),
        file_flag_ro          = sld::bit_value(2),
        file_flag_rw          = sld::bit_value(3),
        file_flag_io_pending  = sld::bit_value(4),
        file_flag_io_complete = sld::bit_value(5),
        file_flag_read        = sld::bit_value(6),
        file_flag_write       = sld::bit_value(7)
    };

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_API const file_handle_t file_open_ro                (const cchar* path);
    IFB_ENG_API const file_handle_t file_open_rw                (const cchar* path);
    IFB_ENG_API bool                file_close                  (const file_handle_t file_handle);
    IFB_ENG_API void                file_reset                  (const file_handle_t file_handle);
    IFB_ENG_API u64                 file_get_size               (const file_handle_t file_handle);
    IFB_ENG_API const cchar*        file_get_path               (const file_handle_t file_handle); 
    IFB_ENG_API const file_error_t  file_get_error              (const file_handle_t file_handle);
    IFB_ENG_API const file_flags_t  file_get_flags              (const file_handle_t file_handle);
    IFB_ENG_API u64                 file_get_length_transferred (const file_handle_t file_handle);
    IFB_ENG_API bool                file_read                   (const file_handle_t file_handle, file_buffer_t* file_buffer);
    IFB_ENG_API bool                file_write                  (const file_handle_t file_handle, file_buffer_t* file_buffer);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct file_buffer_t {
        byte* data;
        u64   size;
        u64   cursor;
        u64   transferred;
    };

    struct file_path_t {
        cchar* buffer;
    };

    struct file_t {
        file_handle_t handle;
        file_buffer_t buffer;
        file_error_t  error;
        file_flags_t  flags;
    };
};

#endif  //IFB_ENGINE_FILE_HPP