#pragma once

#include <stdio.h>
#include <sld-memory.hpp>

#include "ifb-engine-file.hpp"
#include "ifb-engine-file-manager.hpp"

#define table_iterate(index)        for (u32 index = 0; index < _mngr.table.capacity; index++)
#define table_file_is_free(index)   (_mngr.table.array.os_handle[index].val == 0)
#define handle_is_valid(handle)     (handle.val < FILE_MANAGER_TABLE_CAPACITY)  
#define table_get_os_handle(handle) _mngr.table.array.os_handle[handle.val];
#define table_get_os_error(handle)  _mngr.table.array.os_error[handle.val];
#define table_get_os_async(handle)  _mngr.table.array.os_async[handle.val];
#define table_get_path(handle)      _mngr.table.array.path[handle.val];

namespace ifb::eng {

    //-------------------------------------------------------------------
    // STATIC
    //-------------------------------------------------------------------

    IFB_ENG_GLOBAL file_mngr_t      _mngr;
    IFB_ENG_GLOBAL file_os_handle_t _array_os_handle [FILE_MANAGER_TABLE_CAPACITY];
    IFB_ENG_GLOBAL file_os_error_t  _array_os_error  [FILE_MANAGER_TABLE_CAPACITY];  
    IFB_ENG_GLOBAL file_path_t      _array_path      [FILE_MANAGER_TABLE_CAPACITY];
    IFB_ENG_GLOBAL cchar            _path_buffer     [FILE_MANAGER_PATH_BUFFER_SIZE];

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void
    file_mngr_startup(
        void) {


        _mngr.table.capacity = FILE_MANAGER_TABLE_CAPACITY;
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

    IFB_ENG_INTERNAL file_handle_t
    file_mngr_get_next_free_handle(
        void) {

        file_handle_t handle = { FILE_MANAGER_INVALID_HANDLE };

        table_iterate(file) {
            if (table_file_is_free(file)) {
                handle.val = file;
                break;
            }
        }

        return(handle);
    }

    IFB_ENG_INTERNAL file_handle_t
    file_mngr_os_open_file(
        const cchar*                 os_path,
        const sld::os_file_config_t& os_config) {

        file_handle_t handle = file_mngr_get_next_free_handle();
        if (handle_is_valid(handle)) {

            file_os_handle_t&        os_handle = table_get_os_handle (handle);
            file_os_error_t&         os_error  = table_get_os_error  (handle);
            file_os_async_context_t& os_async  = table_get_os_async  (handle);
            file_path_t&             path      = table_get_path      (handle);

            os_error = sld::os_file_open(os_handle, os_path, os_config);
            
            (void)sprintf_s(path.buffer, FILE_MANAGER_PATH_SIZE, "%s", os_path);
        }
        return(handle);
    }


};