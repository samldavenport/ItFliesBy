#ifndef IFB_ENGINE_FILE_MANAGER_HPP
#define IFB_ENGINE_FILE_MANAGER_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-file.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct file_manager_t {
        u32                 capacity;
        file_flags_t*       flags;
        file_error_t*       error;
        file_os_context_t*  os_context;
        file_handle_list_t* hnd_list_open;
        file_handle_list_t* hnd_list_closed;
        file_handle_list_t* hnd_list_pending;
    };
            

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    file_handle_t file_manager_open  (file_manager_t* mngr, const cchar* path, const os_file_config* config);
    bool          file_manager_close (file_manager_t* mngr, const file_handle_t hnd);
    u32           file_manager_size  (file_manager_t* mngr, const file_handle_t hnd);
    file_error_t  file_manager_error (file_manager_t* mngr, const file_handle_t hnd);
    const cchar*  file_manager_path  (file_manager_t* mngr, const file_handle_t hnd);
    file_flags_t  file_manager_flags (file_manager_t* mngr, const file_handle_t hnd);
    bool          file_manager_read  (file_manager_t* mngr, const file_handle_t hnd, file_buffer* buffer);
    bool          file_manager_write (file_manager_t* mngr, const file_handle_t hnd, file_buffer* buffer);


    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------


};

#endif //IFB_ENGINE_FILE_MANAGER_HPP