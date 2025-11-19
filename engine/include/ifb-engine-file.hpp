#ifndef IFB_ENG_FILE_HPP
#define IFB_ENG_FILE_HPP

#include "ifb-engine.hpp"
#include <sld-os.hpp>
#include <sld-array-list.hpp>

#define IFB_ENG_FILE_INVALID_INDEX 0xFFFFFFFF

using namespace sld;

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct file_buffer_t;
    struct file_handle_t;
    struct file_flags_t;
    struct file_error_t;
    struct file_handle_list_t;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_API const file_handle_t file_open_ro_new            (const cchar* path);
    IFB_ENG_API const file_handle_t file_open_ro_existing       (const cchar* path);
    IFB_ENG_API const file_handle_t file_open_ro_always         (const cchar* path);
    IFB_ENG_API const file_handle_t file_open_ro_overwrite      (const cchar* path);
    IFB_ENG_API const file_handle_t file_open_rw_new            (const cchar* path);
    IFB_ENG_API const file_handle_t file_open_rw_existing       (const cchar* path);
    IFB_ENG_API const file_handle_t file_open_rw_always         (const cchar* path);
    IFB_ENG_API const file_handle_t file_open_rw_overwrite      (const cchar* path);
    IFB_ENG_API bool                file_close                  (const file_handle_t file);
    IFB_ENG_API void                file_reset                  (const file_handle_t file);
    IFB_ENG_API u64                 file_get_size               (const file_handle_t file);
    IFB_ENG_API const cchar*        file_get_path               (const file_handle_t file); 
    IFB_ENG_API const file_error_t  file_get_error              (const file_handle_t file);
    IFB_ENG_API const file_flags_t  file_get_flags              (const file_handle_t file);
    IFB_ENG_API bool                file_read                   (const file_handle_t file, file_buffer_t* buffer);
    IFB_ENG_API bool                file_write                  (const file_handle_t file, file_buffer_t* buffer);

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum file_flag_e {
        file_flag_e_none        = 0,
        file_flag_e_error       = bit_value(0),
        file_flag_e_internal    = bit_value(1),
        file_flag_e_ro          = bit_value(2),
        file_flag_e_rw          = bit_value(3),
        file_flag_e_io_pending  = bit_value(4),
        file_flag_e_io_complete = bit_value(5),
        file_flag_e_read        = bit_value(6),
        file_flag_e_write       = bit_value(7)
    };

    struct file_handle_t      : handle_t                    { };
    struct file_flags_t       : flags_t                     { };
    struct file_error_t       : error_t                     { };
    struct file_handle_list_t : array_list_t<file_handle_t> { };

    struct file_os_context_t {
        os_file_handle_t     file_hnd;
        os_file_async_t      async;
        os_file_map_handle_t map_hnd;
        os_file_error_t      error;
    };

    struct file_t {
        cchar*            path;
        file_handle_t     handle;
        file_flags_t      flags;
        file_error_t      error_t;
        file_os_context_t os_context;
    };

    struct file_buffer_t {
        byte* data;
        u64   size;
        u64   cursor;
    };
};

#endif  //IFB_ENGINE_FILE_HPP