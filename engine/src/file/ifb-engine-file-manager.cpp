#pragma once

#include <stdio.h>
#include <sld-memory.hpp>

#include "ifb-engine-file.hpp"
#include "ifb-engine-file-manager.hpp"

#define table_iterate(index)      for (u32 index = 0; index < _mngr.table.capacity; index++)
#define table_file_is_free(index) (_mngr.table.array.os_handle[index].val == 0)
#define file_is_valid(file)       (file.index < FILE_MANAGER_TABLE_CAPACITY)  
#define file_get_os_handle(file)  _mngr.table.array.os_handle[file.index];
#define file_get_os_error(file)   _mngr.table.array.os_error[file.index];
#define file_get_os_async(file)   _mngr.table.array.os_async[file.index];
#define file_get_path(file)       _mngr.table.array.path[file.index];

namespace ifb::eng {

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL file_t file_mngr_get_next_free (void);

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void
    file_mngr_startup(
        void) {

        _mngr.table.capacity        = FILE_MANAGER_TABLE_CAPACITY;
        _mngr.table.array.os_handle = _array_os_handle;
        _mngr.table.array.os_error  = _array_os_error;
        _mngr.table.array.path      = _array_path;

        memset(_path_buffer, 0, FILE_MANAGER_PATH_BUFFER_SIZE);
        u32 path_offset = 0;
        table_iterate(file) {

            _mngr.table.array.os_handle [file].val    = 0;
            _mngr.table.array.os_error  [file].val    = 0;
            _mngr.table.array.path      [file].buffer = &_path_buffer[path_offset];

            path_offset += FILE_MANAGER_PATH_SIZE;
        }
    }

    IFB_ENG_INTERNAL void
    file_mngr_shutdown(
        void) {

    }

    IFB_ENG_INTERNAL file_t
    file_mngr_get_next_free(
        void) {

        file_t file = { FILE_INVALID_INDEX };

        table_iterate(file) {
            if (table_file_is_free(file)) {
                break;
            }
        }

        return(file);
    }

    IFB_ENG_INTERNAL file_t
    file_mngr_os_open_file(
        const file_path_t       path,
        const file_os_config_t& os_config) {

        file_t file = file_mngr_get_next_free();
        if (file_is_valid(file)) {

            file_os_handle_t&        os_handle = file_get_os_handle (file);
            file_os_error_t&         os_error  = file_get_os_error  (file);
            file_os_async_context_t& os_async  = file_get_os_async  (file);
            file_path_t&             os_path   = file_get_path      (file);

            os_error = os_file_open(os_handle, path.buffer, &os_config);
            
            (void)sprintf_s(os_path.buffer, FILE_MANAGER_PATH_SIZE, "%s", path.buffer);
        }
        return(file);
    }

    IFB_ENG_INTERNAL bool
    file_mngr_os_close_file(
        const file_t file) {

        //TODO

        return(false);
    }

    IFB_ENG_INTERNAL bool
    file_mngr_os_read(
        const file_t      file,
        file_os_buffer_t* file_buffer) {

        file_os_handle_t& os_handle = file_get_os_handle (file);
        file_os_error_t&  os_error  = file_get_os_error  (file);

        os_error = os_file_read(os_handle, file_buffer);

        return(os_error.val == os_file_error_e_success);
    }

    IFB_ENG_INTERNAL bool
    file_mngr_os_write(
        const file_t      file,
        file_os_buffer_t* file_buffer) {

        file_os_handle_t& os_handle = file_get_os_handle (file);
        file_os_error_t&  os_error  = file_get_os_error  (file);

        os_error = os_file_write(os_handle, file_buffer);

        return(os_error.val == os_file_error_e_success);
    }

    IFB_ENG_INTERNAL u64
    file_mngr_os_get_size(
        const file_t file) {

        file_os_handle_t& os_handle = file_get_os_handle (file);
        file_os_error_t&  os_error  = file_get_os_error  (file);

        u64 size = 0;
        os_error = os_file_size(os_handle, size);

        return(size);
    }
};