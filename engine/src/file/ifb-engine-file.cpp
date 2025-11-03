#pragma once

#include "ifb-engine-file.hpp"
#include "ifb-engine-file-manager.hpp"


namespace ifb::eng {

    constexpr u32          FILE_INVALID_INDEX = IFB_ENG_FILE_INVALID_INDEX;  
    constexpr file_t       FILE_INVALID       = { FILE_INVALID_INDEX };
    constexpr file_path_t  FILE_PATH_INVALID  = { NULL };
    constexpr file_error_t FILE_ERROR_INVALID = { os_file_error_e_invalid_file }; 
    constexpr file_flags_t FILE_FLAGS_NONE    = { file_flag_none }; 

    IFB_ENG_API const file_t
    file_open_ro_new(
        const file_path_t path) {

        file_os_config_t config;
        config.access_flags.val = os_file_access_flag_e_read;
        config.share_flags.val  = os_file_share_flag_e_read;
        config.mode.val         = os_file_mode_e_create_new;
        config.is_async         = true;

        const file_t file = file_mngr_os_open_file(path, config);
        return(file);
    }

    IFB_ENG_API const file_t
    file_open_ro_existing(
        const file_path_t path) {

        file_os_config_t config;
        config.access_flags.val = os_file_access_flag_e_read;
        config.share_flags.val  = os_file_share_flag_e_read;
        config.mode.val         = os_file_mode_e_open_existing;
        config.is_async         = true;

        const file_t file = file_mngr_os_open_file(path, config);
        return(file);
    }

    IFB_ENG_API const file_t
    file_open_ro_always(
        const file_path_t path) {

        file_os_config_t config;
        config.access_flags.val = os_file_access_flag_e_read;
        config.share_flags.val  = os_file_share_flag_e_read;
        config.mode.val         = os_file_mode_e_open_always;
        config.is_async         = true;

        const file_t file = file_mngr_os_open_file(path, config);
        return(file);
    }

    IFB_ENG_API const file_t
    file_open_ro_overwrite(
        const file_path_t path) {

        file_os_config_t config;
        config.access_flags.val = os_file_access_flag_e_read;
        config.share_flags.val  = os_file_share_flag_e_read;
        config.mode.val         = os_file_mode_e_overwrite_existing;
        config.is_async         = true;

        const file_t file = file_mngr_os_open_file(path, config);
        return(file);
    }

    IFB_ENG_API const file_t
    file_open_rw_new(
        const file_path_t path) {

        file_os_config_t config;
        config.access_flags.val = os_file_access_flag_e_write;
        config.share_flags.val  = os_file_share_flag_e_read;
        config.mode.val         = os_file_mode_e_create_new;
        config.is_async         = true;

        const file_t file = file_mngr_os_open_file(path, config);
        return(file);
    }

    IFB_ENG_API const file_t
    file_open_rw_existing(
        const file_path_t path) {

        file_os_config_t config;
        config.access_flags.val = os_file_access_flag_e_write;
        config.share_flags.val  = os_file_share_flag_e_read;
        config.mode.val         = os_file_mode_e_open_existing;
        config.is_async         = true;

        const file_t file = file_mngr_os_open_file(path, config);
        return(file);
    }

    IFB_ENG_API const file_t
    file_open_rw_always(
        const file_path_t path) {

        file_os_config_t config;
        config.access_flags.val = os_file_access_flag_e_write;
        config.share_flags.val  = os_file_share_flag_e_read;
        config.mode.val         = os_file_mode_e_open_always;
        config.is_async         = true;

        const file_t file = file_mngr_os_open_file(path, config);
        return(file);
    }

    IFB_ENG_API const file_t
    file_open_rw_overwrite(
        const file_path_t path) {

        file_os_config_t config;
        config.access_flags.val = os_file_access_flag_e_write;
        config.share_flags.val  = os_file_share_flag_e_read;
        config.mode.val         = os_file_mode_e_overwrite_existing;
        config.is_async         = true;

        const file_t file = file_mngr_os_open_file(path, config);
        return(file);
    }
     

    IFB_ENG_API bool
    file_close(
        const file_t file) {

        return(false);
    }

    IFB_ENG_API void
    file_reset(
        const file_t file) {

    }

    IFB_ENG_API u64
    file_get_size(
        const file_t file) {

        return(0);
    }

    IFB_ENG_API const file_path_t  
    file_get_path(
        const file_t file) {

        const file_path_t path = file_mngr_file_is_valid(file)
            ? file_mngr_get_path(file)
            : FILE_PATH_INVALID;

        return(path);
    } 

    IFB_ENG_API const file_error_t
    file_get_error(
        const file_t file) {

        const file_error_t error = file_mngr_file_is_valid(file)
            ? file_mngr_get_os_error(file)
            : FILE_ERROR_INVALID;

        return(error);
    }

    IFB_ENG_API const file_flags_t
    file_get_flags(
        const file_t file) {

        const file_flags_t flags = file_mngr_file_is_valid(file)
            ? file_mngr_get_flags(file)
            : FILE_FLAGS_NONE;
            
        return(flags);
    }

    IFB_ENG_API void
    file_get_info(
        const file_t file,
        file_info_t* info) {
        
        assert(info != NULL);

        if (file_mngr_file_is_valid(file)) {
            info->path  = file_mngr_get_path(file);
            info->flags = file_mngr_get_flags(file);
            info->error = file_mngr_get_os_error(file);
        }
        else {
            info->path  = FILE_PATH_INVALID;
            info->flags = FILE_FLAGS_NONE;
            info->error = FILE_ERROR_INVALID;
        }
    }

    IFB_ENG_API bool
    file_read(
        const file_t      file,
        file_os_buffer_t* file_buffer) {

        return(false);
    }

    IFB_ENG_API bool
    file_write(
        const file_t      file,
        file_os_buffer_t* file_buffer) {

        return(false);
    }
};