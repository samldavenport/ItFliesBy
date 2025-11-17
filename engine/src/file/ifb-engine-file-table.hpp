#ifndef IFB_ENGINE_FILE_TABLE_HPP
#define IFB_ENGINE_FILE_TABLE_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-file.hpp"
#include <sld-os.hpp>

namespace ifb::eng {


    struct file_table_t {
        u32    count;
        u32    path_stride;
        cchar* path_buffer;
        struct {
            os_file_t*               os_file;
            os_file_async_t*         os_async;
            os_file_mapped_buffer_t* os_mapped_buffer;
            os_file_error_s32*       os_error;
            cchar**                  path;
        } array;
    };

    file_table_t* file_table_create          (const u32     count);
    void          file_table_destroy         (file_table_t* file_table);
    file_hnd_t    file_table_get_free_handle (file_table_t* file_table);



};

#endif //IFB_ENGINE_FILE_TABLE_HPP
