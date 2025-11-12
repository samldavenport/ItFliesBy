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

    struct asset_s32_error_t : eng_error_s32_t { };
    struct asset_u32_id_t    : u32_t       { };
    struct asset_u32_type_t  : u32_t       { };
    struct asset_h32_text_t  : h32_t       { };
    struct asset_h32_image_t : h32_t       { };
    struct asset_h32_sound_t : h32_t       { };
    struct asset_h32_font_t  : h32_t       { };

    struct asset_buffer_t : sld::buffer_t { };
    struct asset_string_t;

    typedef u64 eng_asset_u64_size_t;

    IFB_ENG_API void                             eng_asset_generate_id         (const u32 i_count, const eng_asset_string_t* i_name, eng_asset_u32_id_t* o_id);
    IFB_ENG_API void                             eng_asset_name_sanitize       (const u32 i_count, eng_asset_string_t* io_name);

    IFB_ENG_API const eng_asset_h32_text_t       eng_asset_mngr_load_text      (const eng_asset_u32_id_t id);
    IFB_ENG_API const eng_asset_h32_image_t      eng_asset_mngr_load_image     (const eng_asset_u32_id_t id);
    IFB_ENG_API const eng_asset_h32_sound_t      eng_asset_mngr_load_sound     (const eng_asset_u32_id_t id);
    IFB_ENG_API const eng_asset_h32_font_t       eng_asset_mngr_load_font      (const eng_asset_u32_id_t id);
    IFB_ENG_API const eng_asset_s32_error_t      eng_asset_mngr_get_last_error (void); 

    enum eng_asset_e32_type_ {
        eng_asset_e32_type_text  = 0,
        eng_asset_e32_type_image = 1,
        eng_asset_e32_type_sound = 2,
        eng_asset_e32_type_font  = 3,
        eng_asset_e32_type_count = 4
    };

    struct eng_asset_index_t {
        eng_asset_u32_id_t   id;
        eng_asset_u32_type_t type;
        eng_asset_u64_size_t offset;
        eng_asset_u64_size_t size;
    };

    struct eng_asset_string_t {
        cchar chars[IFB_ENG_ASSET_CSTR_SIZE];
    };
};

#endif //IFB_ENGINE_ASSET_HPP