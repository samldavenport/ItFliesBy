#ifndef IFB_ENGINE_ASSET_HPP
#define IFB_ENGINE_ASSET_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-file.hpp"
#include "ifb-engine-id.hpp"

#ifndef    IFB_ENG_ASSET_DB_PATH   
#   define IFB_ENG_ASSET_DB_PATH           "IFB.AssetDB.ifb"
#endif
#ifndef    IFB_ENG_ASSET_VERIF_STR   
#   define IFB_ENG_ASSET_VERIF_STR         "IFBASSETDATABASE"
#endif
#ifndef    IFB_ENG_ASSET_CONFIG_PATH   
#   define IFB_ENG_ASSET_CONFIG_PATH       "IFB.AssetConfig.xml"
#endif
#ifndef    IFB_ENG_ASSET_CSTR_SIZE
#   define IFB_ENG_ASSET_CSTR_SIZE         32 
#endif
#ifndef    IFB_ENG_ASSET_XML_STACK_SIZE_KB
#   define IFB_ENG_ASSET_XML_STACK_SIZE_KB 4
#endif

namespace ifb::eng {

    struct asset_error_t  : error_t  { };
    struct asset_id_t     : u32_t    { };
    struct asset_type_t   : u32_t    { };
    struct asset_text_t   : u32_t    { };
    struct asset_image_t  : u32_t    { };
    struct asset_sound_t  : u32_t    { };
    struct asset_font_t   : u32_t    { };
    struct asset_buffer_t : buffer_t { };
    struct asset_string_t;

    IFB_ENG_API void                asset_generate_id    (const u32 i_count, const asset_string_t* i_name, asset_id_t* o_id);
    IFB_ENG_API void                asset_name_sanitize  (const u32 i_count, asset_string_t* io_name);

    IFB_ENG_API const asset_text_t  asset_load_text      (const asset_id_t id);
    IFB_ENG_API const asset_image_t asset_load_image     (const asset_id_t id);
    IFB_ENG_API const asset_sound_t asset_load_sound     (const asset_id_t id);
    IFB_ENG_API const asset_font_t  asset_load_font      (const asset_id_t id);
    IFB_ENG_API const asset_error_t asset_get_last_error (void); 

    enum asset_type_e {
        asset_type_e_text  = 0,
        asset_type_e_image = 1,
        asset_type_e_sound = 2,
        asset_type_e_font  = 3,
        asset_type_e_count = 4
    };

    struct asset_index_t {
        asset_id_t   id;
        asset_type_t type;
        u64          offset;
        u64          size;
    };

    struct asset_string_t {
        cchar chars[IFB_ENG_ASSET_CSTR_SIZE];
    };
};

#endif //IFB_ENGINE_ASSET_HPP