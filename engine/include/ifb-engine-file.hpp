#ifndef IFB_ENG_FILE_HPP
#define IFB_ENG_FILE_HPP

#include "ifb-engine.hpp"
#include <sld-os.hpp>

#ifndef    IFB_ENG_FILE_PATH_SIZE
#   define IFB_ENG_FILE_PATH_SIZE 128
#endif
#ifndef    IFB_ENG_FILE_TABLE_CAPACITY
#   define IFB_ENG_FILE_TABLE_CAPACITY 128
#endif
#ifndef    IFB_ENG_FILE_BUFFER_SIZE_KB
#   define IFB_ENG_FILE_BUFFER_SIZE_KB 128
#endif

#define IFB_ENG_FILE_H32_INVALID 0xFFFFFFFF

namespace ifb::eng {

    using file_error_s32_t = eng_error_s32_t;
    using file_buffer_t    = sld::os_file_buffer_t;
    using file_path_t      = sld::os_file_path_cstr_t ;
    using file_h32_t       = h32_t;
    using file_flags_u32_t = u32_t;

    IFB_ENG_API const file_h32_t       file_open_ro               (const cchar*      file_path);
    IFB_ENG_API const file_h32_t       file_open_rw               (const cchar*      file_path);
    IFB_ENG_API bool                   file_close                 (const file_h32_t  file_handle);
    IFB_ENG_API const u64              file_get_size              (const file_h32_t  file_handle);
    IFB_ENG_API const file_flags_u32_t file_get_flags             (const file_h32_t  file_handle);
    IFB_ENG_API const cchar*           file_get_path              (const file_h32_t  file_handle);
    IFB_ENG_API const file_error_s32_t file_get_last_error        (const file_h32_t  file_handle = { IFB_ENG_FILE_H32_INVALID} );
    IFB_ENG_API bool                   file_read                  (const file_h32_t  file_handle, file_buffer_t& read_buffer);
    IFB_ENG_API bool                   file_write                 (const file_h32_t  file_handle, file_buffer_t& write_buffer);
    IFB_ENG_API bool                   file_read_async            (const file_h32_t  file_handle);
    IFB_ENG_API bool                   file_write_async           (const file_h32_t  file_handle);

    enum file_flag_e32_ {
        file_flag_e32_none        = 0,
        file_flag_e32_error       = sld::bit_value(0),
        file_flag_e32_ro          = sld::bit_value(1),
        file_flag_e32_rw          = sld::bit_value(2),
        file_flag_e32_io_pending  = sld::bit_value(3),
        file_flag_e32_io_complete = sld::bit_value(4),
        file_flag_e32_read        = sld::bit_value(5),
        file_flag_e32_write       = sld::bit_value(6)
    };

    enum file_error_e32_ {
        file_error_e32_success               = 0x10020000,
        file_error_e32_warning               = 0x00020000,
        file_error_e32_failure               = 0x80020000,
        file_error_e32_unknown               = 0x80020001,
        file_error_e32_invalid_args          = 0x80020002,
        file_error_e32_invalid_handle        = 0x80020003,
        file_error_e32_invalid_disk          = 0x80020004,
        file_error_e32_invalid_device        = 0x80020005,
        file_error_e32_invalid_buffer        = 0x80020006,
        file_error_e32_invalid_file          = 0x80020007,
        file_error_e32_sharing_violation     = 0x80020008,
        file_error_e32_already_exists        = 0x80020009,
        file_error_e32_not_found             = 0x8002000A,
        file_error_e32_access_denied         = 0x8002000B,
        file_error_e32_pipe_busy             = 0x8002000C,
        file_error_e32_reached_end_of_file   = 0x8002000D,
        file_error_e32_broken_pipe           = 0x8002000E,
        file_error_e32_no_data               = 0x8002000F,
        file_error_e32_more_data             = 0x80020010,
        file_error_e32_io_incomplete         = 0x80020011,
        file_error_e32_io_pending            = 0x80020012,
        file_error_e32_operation_aborted     = 0x80020013,
        file_error_e32_disk_io_failure       = 0x80020014,
        file_error_e32_disk_corrupt          = 0x80020015,
        file_error_e32_device_not_ready      = 0x80020016,
        file_error_e32_out_of_memory         = 0x80020017,
        file_error_e32_device_failure        = 0x80020018,
        file_error_e32_arena_commit_fail     = 0x80020019,
        file_error_e32_buffer_alloc_fail     = 0x8002001A,
    };
};

#endif  //IFB_ENGINE_FILE_HPP