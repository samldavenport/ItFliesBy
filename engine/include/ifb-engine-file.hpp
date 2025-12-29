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

    struct file_buffer;
    struct file_handle;
    struct file_flags;
    struct file_error;
    struct file_handle_list;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_API const file_handle  file_open_ro_new            (const cchar* path);
    IFB_ENG_API const file_handle  file_open_ro_existing       (const cchar* path);
    IFB_ENG_API const file_handle  file_open_ro_always         (const cchar* path);
    IFB_ENG_API const file_handle  file_open_ro_overwrite      (const cchar* path);
    IFB_ENG_API const file_handle  file_open_rw_new            (const cchar* path);
    IFB_ENG_API const file_handle  file_open_rw_existing       (const cchar* path);
    IFB_ENG_API const file_handle  file_open_rw_always         (const cchar* path);
    IFB_ENG_API const file_handle  file_open_rw_overwrite      (const cchar* path);
    IFB_ENG_API bool               file_close                  (const file_handle file);
    IFB_ENG_API void               file_reset                  (const file_handle file);
    IFB_ENG_API u64                file_get_size               (const file_handle file);
    IFB_ENG_API const cchar*       file_get_path               (const file_handle file); 
    IFB_ENG_API const file_error   file_get_error              (const file_handle file);
    IFB_ENG_API const file_flags   file_get_flags              (const file_handle file);
    IFB_ENG_API bool               file_read                   (const file_handle file, file_buffer* buffer);
    IFB_ENG_API bool               file_write                  (const file_handle file, file_buffer* buffer);

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

    struct file_handle      : handle                    { };
    struct file_flags       : flags                     { };
    struct file_error       : error                     { };
    struct file_handle_list : array_list<file_handle> { };

    struct file_os_manager {
        os_file_handle     file_hnd;
        os_file_async      async;
        os_file_map_handle map_hnd;
        os_file_error      error;
    };

    struct file {
        cchar*            path;
        file_handle     handle;
        file_flags      flags;
        file_error      error_t;
        file_os_manager os_manager;
    };

    struct file_buffer {
        byte* data;
        u64   size;
        u64   cursor;
    };
};

#endif  //IFB_ENGINE_FILE_HPP