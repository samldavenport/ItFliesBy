#pragma once

#include <sld-memory.hpp>
#include "ifb-engine-file.hpp"
#include "ifb-engine-file-manager.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // STATIC
    //-------------------------------------------------------------------

    static file_mngr_t             _file_mngr;
    static file_os_context_t       _os_context       [IFB_ENG_FILE_TABLE_CAPACITY];
    static file_callback_context_t _callback_context [IFB_ENG_FILE_TABLE_CAPACITY];
    static file_t                  _file             [IFB_ENG_FILE_TABLE_CAPACITY];
    static cchar                   _path_buffer      [IFB_ENG_FILE_TABLE_CAPACITY * IFB_ENG_FILE_PATH_SIZE];
    static file_path_t             _working_directory;

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------
 
    file_t*               file_mngr_get_next_closed      (void);
    file_t*               file_mngr_get_next_open        (void);
    void                  file_mngr_add_closed           (file_t* file);
    void                  file_mngr_add_open             (file_t* file);
    void                  file_mngr_async_callback_read  (const void* data, const file_os_error_t error, const u32 bytes_transferred);
    void                  file_mngr_async_callback_write (const void* data, const file_os_error_t error, const u32 bytes_transferred);
    const eng_error_s32_t file_mngr_error_os_to_eng      (const file_os_error_t    os_error);  

    //-------------------------------------------------------------------
    // API
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL const file_h32_t
    file_mngr_open_ro(
        const cchar* file_path) {

        // get the next unopened file struct
        file_h32_t handle = { IFB_ENG_FILE_H32_INVALID };
        file_t*    file   = file_mngr_get_next_closed ();
        if (file == NULL) return(handle);

        // config
        static const sld::os_file_access_flags_t access_flags = { sld::os_file_access_flag_e_read };
        static const sld::os_file_share_flags_t  share_flags  = { sld::os_file_share_flag_e_read  };
        static const sld::os_file_mode_t         mode         = { sld::os_file_mode_e_open_always };
        static const bool                    is_async     = false;
        static const sld::os_file_config_t os_file_config = {
            access_flags,
            share_flags,
            mode,
            is_async
        };

        // open the file
        sld::os_file_error_t os_error = sld::os_file_open(
            file->os_handle,
            file_path,
            os_file_config);

        _file_mngr.last_error = file_mngr_error_os_to_eng(os_error); 

        if (_file_mngr.last_error.val != file_error_e32_success) {
            file_mngr_add_closed(file);
            return(handle);
        }        

        // commit memory
        eng_mem_arena_t* arena = eng_mem_arena_commit_file(); 
        if (arena == NULL) {
            _file_mngr.last_error.val = file_error_e32_arena_commit_fail;
            file_mngr_add_closed(file);
            return(handle);            
        }

        // initialize file
        file->arena = arena;

        // copy path
        for (
            u32 index = 0;
            index < _file_mngr.path_size;
            ++index) {

            const cchar c = file_path[index];
            file->path[index] = c;

            if (c == 0) break;
        }

        // set the handle
        handle.val = file->index;
        return(handle);
    }

    IFB_ENG_INTERNAL const file_h32_t
    file_mngr_open_rw(
        const cchar* file_path) {

        // get the next unopened file struct
        file_h32_t handle = {IFB_ENG_FILE_H32_INVALID};
        file_t*    file   = file_mngr_get_next_closed ();
        if (file == NULL) return(handle);

        // config
        static const sld::os_file_access_flags_t access_flags = { sld::os_file_access_flag_e_read | sld::os_file_access_flag_e_write };
        static const sld::os_file_share_flags_t  share_flags  = { sld::os_file_share_flag_e_read  };
        static const sld::os_file_mode_t         mode         = { sld::os_file_mode_e_open_always };
        static const bool                    is_async     = false;
        static const sld::os_file_config_t os_file_config = {
            access_flags,
            share_flags,
            mode,
            is_async
        };

        // open the file
        sld::os_file_error_t os_error = sld::os_file_open(
            file->os_handle,
            file_path,
            os_file_config);

        _file_mngr.last_error = file_mngr_error_os_to_eng(os_error); 

        if (_file_mngr.last_error.val != file_error_e32_success) {
            file_mngr_add_closed(file);
            return(handle);
        }        

        // commit memory        
        eng_mem_arena_t* arena = eng_mem_arena_commit_file(); 
        if (arena == NULL) {
            _file_mngr.last_error.val = file_error_e32_arena_commit_fail;
            file_mngr_add_closed(file);
            return(handle);          
        }

        // initialize the file
        file->arena = arena;

        // copy path
        for (
            u32 index = 0;
            index < _file_mngr.path_size;
            ++index) {

            const cchar c = file_path[index];
            file->path[index] = c;

            if (c == 0) break;
        }

        // set the handle
        handle.val = file->index; 
        return(handle);
    }

    IFB_ENG_INTERNAL bool
    file_mngr_close(
        const file_h32_t file_handle) {

        return(false);
    }

    IFB_ENG_INTERNAL const u64
    file_mngr_get_size(
        const file_h32_t file_handle) {

        file_t* file = file_mngr_get_file(file_handle);
        if (file == NULL) {
            _file_mngr.last_error.val = file_error_e32_invalid_file;
            return(false);
        } 

        u64 size = 0;
        const file_os_error_t os_error = sld::os_file_size(
            file->os_handle,
            size
        );

        file->last_error = file_mngr_error_os_to_eng(os_error);
        
        return(size);
    }

    IFB_ENG_INTERNAL const file_flags_u32_t
    file_mngr_get_flags(
        const file_h32_t file_handle) {

        file_t* file = file_mngr_get_file(file_handle);
        
        file_flags_u32_t flags;
        flags.val = (file != NULL) 
            ? file->flags.val
            : file_error_e32_invalid_file; 

        return(flags);
    }

    IFB_ENG_INTERNAL const cchar*
    file_mngr_get_path(
        const file_h32_t file_handle) {

        file_t* file = file_mngr_get_file(file_handle);
        if (file == NULL) {
            _file_mngr.last_error.val = file_error_e32_invalid_file;
            return(NULL);
        } 
        
        return(file->path);
    }

    IFB_ENG_API bool
    file_mngr_update_buffer(
        const file_h32_t file_handle,
        const u32        length,
        const u32        cursor,
        const byte*      data) {

        file_t* file = file_mngr_get_file(file_handle);
        if (file == NULL) {
            _file_mngr.last_error.val = file_error_e32_invalid_file;
            return(false);
        } 



        return(true);
    }

    IFB_ENG_API const file_error_s32_t
    file_mngr_get_last_error(
        const file_h32_t file_handle) {

        if (file_handle.val == IFB_ENG_FILE_H32_INVALID) {
            return(_file_mngr.last_error);    
        }

        const file_t* file = file_mngr_get_file(file_handle);

        file_error_s32_t last_error;
        last_error.val = (file != NULL)
            ? file->last_error.val
            : file_error_e32_invalid_file;
    
        return(last_error);
    }

    IFB_ENG_INTERNAL bool
    file_mngr_read(
        const file_h32_t file_handle,
        file_buffer_t&   read_buffer) {

        // validate the file and make sure there's no pending operation
        file_t* file = file_mngr_get_file(file_handle);
        if (!file) {
            _file_mngr.last_error.val = file_error_e32_invalid_file;
            return(false);
        }
        if (file->flags.val & file_flag_e32_io_pending) {
            return(false);
        }

        // initialize the async context
        file_os_async_context_t& async_context = file->os_async_context;
        async_context.callback->data  = (void*)file;
        async_context.callback->func  = _file_mngr.os_callback_read; 

        // do the read
        const sld::os_file_error_t os_error = sld::os_file_read(
            file->os_handle,
            read_buffer
        );

        // set the last error
        // update flags if we didn't succeed
        file->last_error      = file_mngr_error_os_to_eng(os_error);
        const bool is_success = (file->last_error.val == file_error_e32_success);
        if (!is_success) {
            file->flags.val |= ~(file_flag_e32_error);
        }
        else {

            //terminate the buffer
            if (read_buffer.length == read_buffer.size) {
                --read_buffer.transferred;
                --read_buffer.cursor;
                read_buffer.data[read_buffer.length - 1] = 0;                
            } 
            else {
                read_buffer.data[read_buffer.length] = 0;
                ++read_buffer.length;
                ++read_buffer.cursor;
                ++read_buffer.transferred;

            }
        }
        return(is_success);
    }

    // IFB_ENG_INTERNAL bool
    // file_mngr_read_async(
    //     const file_h32_t file_handle) {

    //     // validate the file and make sure there's no pending operation
    //     file_t* file = file_mngr_get_file(file_handle);
    //     if (!file) {
    //         _file_mngr.last_error.val = file_error_e32_invalid_file;
    //         return(false);
    //     }
    //     if (file->flags.val & file_flag_e32_io_pending) {
    //         return(false);
    //     }

    //     // set the read and pending io flags
    //     file->flags.val |= (file_flag_e32_read | file_flag_e32_io_pending);

    //     // initialize the async context
    //     file_os_async_context_t& async_context = file->os_async_context;
    //     async_context.callback->data  = (void*)file;
    //     async_context.callback->func  = _file_mngr.os_callback_read; 

    //     // do the async read
    //     const sld::os_file_error_t os_error = sld::os_file_read_async(
    //         file->os_handle,
    //         file->os_buffer,
    //         async_context
    //     );

    //     // set the last error
    //     // update flags if we didn't succeed
    //     file->last_error      = file_mngr_error_os_to_eng(os_error);
    //     const bool is_success = (file->last_error.val != file_error_e32_success);
    //     if (!is_success) {
    //         file->flags.val &= ~(file_flag_e32_read | file_flag_e32_io_pending);
    //         file->flags.val |= ~(file_flag_e32_error);
    //     }
    //     return(is_success);
    // }

    IFB_ENG_INTERNAL bool
    file_mngr_write(
        const file_h32_t file_handle,
        file_buffer_t&   write_buffer) {

        // validate the file and make sure there's no pending operation
        file_t* file = file_mngr_get_file(file_handle);
        if (!file) {
            _file_mngr.last_error.val = file_error_e32_invalid_file;
            return(false);
        }
        const bool is_args_valid = (write_buffer.size != 0 && write_buffer.data != NULL);
        if (!is_args_valid) {
            file->last_error.val = file_error_e32_invalid_args;
            return(false);
        }
        if (file->flags.val & file_flag_e32_io_pending) {
            file->last_error.val = file_error_e32_io_pending;
            return(false);
        }

        // ensure we don't include null terminator        
        const u32  terminator_index = (write_buffer.length - 1);
        const cchar   last_char        = write_buffer.data[terminator_index];
        const bool is_terminated    = (last_char == 0);
        if (is_terminated) {
            --write_buffer.length;
        }

        // do the write
        const sld::os_file_error_t os_error = sld::os_file_write(
            file->os_handle,
            write_buffer
        );

        // set the last error
        // update flags if we didn't succeed
        file->last_error      = file_mngr_error_os_to_eng(os_error);
        const bool is_success = (file->last_error.val == file_error_e32_success);
        if (!is_success) {
            file->flags.val |= ~(file_flag_e32_error);
        }
        if (is_terminated) {
            ++write_buffer.length;
        }
        return(is_success);
    }

    // IFB_ENG_INTERNAL bool
    // file_mngr_write_async(
    //     const file_h32_t file_handle) {

    //     // validate the file and make sure there's no pending operation
    //     file_t* file = file_mngr_get_file(file_handle);
    //     if (!file) {
    //         _file_mngr.last_error.val = file_error_e32_invalid_file;
    //         return(false);
    //     }
    //     if (file->flags.val & file_flag_e32_io_pending) {
    //         return(false);
    //     }

    //     // set the write and pending io flags
    //     file->flags.val |= file_flag_e32_write | file_flag_e32_io_pending;

    //     // initialize the async context
    //     file_os_async_context_t& async_context = file->os_async_context;
    //     async_context.callback->data  = (void*)file;
    //     async_context.callback->func  = _file_mngr.os_callback_write;
        
    //     // do the async write
    //     const sld::os_file_error_t os_error = sld::os_file_write_async(
    //         file->os_handle,
    //         file->os_buffer,
    //         async_context
    //     );

    //     // set the last error
    //     // update flags if we didn't succeed
    //     file->last_error      = file_mngr_error_os_to_eng(os_error);
    //     const bool is_success = (file->last_error.val != file_error_e32_success);
    //     if (!is_success) {
    //         file->flags.val &= ~(file_flag_e32_write | file_flag_e32_io_pending);
    //         file->flags.val |= ~(file_flag_e32_error);
    //     }
    //     return(is_success);
    // }

    IFB_ENG_API const cchar*
    file_mngr_get_working_directory(
        void) {

        static const cchar* dir = _working_directory.buffer; 
        return(dir);
    }

    //-------------------------------------------------------------------
    // INTERNAL
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void
    file_mngr_startup(
        void) {

        const bool is_initialized = (_file_mngr.capacity != 0);  
        if (is_initialized) return;

        sld::os_file_error_t os_error = sld::os_file_get_working_directory(_working_directory);
        assert(os_error.val == sld::os_file_error_e_success);

        _file_mngr.os_callback_read  = file_mngr_async_callback_read;
        _file_mngr.os_callback_write = file_mngr_async_callback_write;
        _file_mngr.buffer_size       = sld::size_kilobytes(IFB_ENG_FILE_BUFFER_SIZE_KB);
        _file_mngr.capacity          = IFB_ENG_FILE_TABLE_CAPACITY;
        _file_mngr.path_size         = IFB_ENG_FILE_PATH_SIZE;
        _file_mngr.list.closed       = _file;

        for (
            u32 file_index = 0;
            file_index < _file_mngr.capacity;
            ++file_index) {

            file_t* current = &_file[file_index];

            current->next                      = (file_index < (_file_mngr.capacity - 1)) ? &_file[file_index + 1] : NULL;
            current->prev                      = (file_index > 0)                         ? &_file[file_index - 1] : NULL;
            current->path                      = &_path_buffer      [file_index * _file_mngr.path_size];
            current->os_async_context.callback = &_callback_context [file_index];
            current->os_async_context.os       = &_os_context       [file_index]; 
            current->index                     = file_index;
        }
    }

    IFB_ENG_INTERNAL void
    file_mngr_async_callback_read(
        const void*           data,
        const file_os_error_t os_error,
        const u32             bytes_transferred) {
        
        if (!data) return;

        file_t* file = (file_t*)data;

        file->last_error          = file_mngr_error_os_to_eng(os_error);
        file->flags.val          &= ~(file_flag_e32_io_pending | file_flag_e32_read);
        file->flags.val          |=  (file->last_error.val == file_error_e32_success)
            ? file_flag_e32_io_complete
            : file_flag_e32_error; 
    }

    IFB_ENG_INTERNAL void
    file_mngr_async_callback_write(
        const void*           data,
        const file_os_error_t os_error,
        const u32             bytes_transferred) {

        if (!data) return;

        file_t* file = (file_t*)data;

        file->last_error          = file_mngr_error_os_to_eng(os_error);
        file->flags.val          &= ~(file_flag_e32_io_pending | file_flag_e32_write);
        file->flags.val          |=  (file->last_error.val == file_error_e32_success)
            ? file_flag_e32_io_complete
            : file_flag_e32_error; 
    }

    IFB_ENG_INTERNAL const eng_error_s32_t
    file_mngr_error_os_to_eng(
        const file_os_error_t os_error) {

        constexpr eng_error_s32_t os_error_map[] = {
            { file_error_e32_success             }, // os_file_error_e_success
            { file_error_e32_unknown             }, // os_file_error_e_unknown
            { file_error_e32_invalid_args        }, // os_file_error_e_invalid_args
            { file_error_e32_invalid_handle      }, // os_file_error_e_invalid_handle
            { file_error_e32_invalid_disk        }, // os_file_error_e_invalid_disk
            { file_error_e32_invalid_device      }, // os_file_error_e_invalid_device
            { file_error_e32_invalid_buffer      }, // os_file_error_e_invalid_buffer
            { file_error_e32_invalid_file        }, // os_file_error_e_invalid_file
            { file_error_e32_sharing_violation   }, // os_file_error_e_sharing_violation
            { file_error_e32_already_exists      }, // os_file_error_e_already_exists
            { file_error_e32_not_found           }, // os_file_error_e_not_found
            { file_error_e32_access_denied       }, // os_file_error_e_access_denied
            { file_error_e32_pipe_busy           }, // os_file_error_e_pipe_busy
            { file_error_e32_reached_end_of_file }, // os_file_error_e_reached_end_of_file
            { file_error_e32_broken_pipe         }, // os_file_error_e_broken_pipe
            { file_error_e32_no_data             }, // os_file_error_e_no_data
            { file_error_e32_more_data           }, // os_file_error_e_more_data
            { file_error_e32_io_incomplete       }, // os_file_error_e_io_incomplete
            { file_error_e32_io_pending          }, // os_file_error_e_io_pending
            { file_error_e32_operation_aborted   }, // os_file_error_e_operation_aborted
            { file_error_e32_disk_io_failure     }, // os_file_error_e_disk_io_failure
            { file_error_e32_disk_corrupt        }, // os_file_error_e_disk_corrupt
            { file_error_e32_device_not_ready    }, // os_file_error_e_device_not_ready
            { file_error_e32_out_of_memory       }, // os_file_error_e_out_of_memory
            { file_error_e32_device_failure      }, // os_file_error_e_device_failure
        };

        constexpr u32 os_error_map_count = sizeof(os_error_map) / sizeof(eng_error_s32_t);


        const eng_error_s32_t eng_error = {(os_error.val < 0 || os_error.val > os_error_map_count)
            ? file_error_e32_unknown
            : os_error_map[os_error.val].val
        };

        return(eng_error);
    }

    IFB_ENG_INTERNAL file_t*
    file_mngr_get_file(
        const file_h32_t file_handle) {

        if (file_handle.val >= _file_mngr.capacity) return(NULL);

        file_t* file     = &_file[file_handle.val]; 
        const bool  is_valid = (file->index == file_handle.val);
        
        return(is_valid ? file : NULL);
    }
    
    IFB_ENG_INTERNAL file_t*
    file_mngr_get_next_closed(
        void) {

        file_t* closed = _file_mngr.list.closed;

        if (closed) {

            file_t* next = closed->next;
            if (next) next->prev = NULL;
            _file_mngr.list.closed = next;
            closed->next = NULL;
            closed->prev = NULL;
        }

        return(closed);
    } 
    
    IFB_ENG_INTERNAL file_t*
    file_mngr_get_next_open(
        void) {

        file_t* open = _file_mngr.list.opened;

        if (open) {

            file_t* next = open->next;
            if (next) next->prev   = NULL;
            _file_mngr.list.opened = next;
            open->next = NULL;
            open->prev = NULL;
        }

        return(open);
    }

    IFB_ENG_INTERNAL void
    file_mngr_add_closed(
        file_t* file) {

        file_t* next = file->next; 
        file_t* prev = file->prev;

        if (next) next->prev = prev;
        if (prev) prev->next = next;
        
        next = _file_mngr.list.closed;
        if (next) next->prev = file;
        file->next = next;
        _file_mngr.list.closed = file;
    }

    IFB_ENG_INTERNAL void
    file_mngr_add_open(
        file_t* file) {

        file_t* next = file->next; 
        file_t* prev = file->prev;

        if (next) next->prev = prev;
        if (prev) prev->next = next;
        
        next = _file_mngr.list.opened;
        if (next) next->prev = file;
        file->next = next;
        _file_mngr.list.opened = file;
    }
};