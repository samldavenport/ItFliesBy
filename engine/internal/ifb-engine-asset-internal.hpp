#ifndef IFB_ENG_ASSET_INTERNAL_HPP
#define IFB_ENG_ASSET_INTERNAL_HPP

#include <sld-xml.hpp>
#include <sld-memory.hpp>
#include <sld-block-allocator.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-hash.hpp"
#include "ifb-engine-asset.hpp"
#include "ifb-engine-memory-internal.hpp"
#include "ifb-engine-file-manager.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using eng_asset_block_alctr_t = sld::block_allocator_t;

    struct eng_asset_block_t;
    struct eng_asset_slot_t;

    struct eng_asset_mngr_t;

    struct eng_asset_db_t;
    struct eng_asset_db_table_t;
    struct eng_asset_db_builder_t;
    struct eng_asset_db_record_t;

    struct eng_asset_db_t;
    struct eng_asset_db_file_index_t;
    struct eng_asset_db_file_verif_t;
    struct eng_asset_db_file_header_t;
    struct eng_asset_db_file_t;
    struct eng_asset_db_builder_t;

    //-------------------------------------------------------------------
    // ASSET
    //-------------------------------------------------------------------

    struct eng_asset_slot_t {
        eng_asset_block_alctr_t* alctr;
        eng_asset_slot_t*        next;
        eng_asset_slot_t*        prev;
        eng_mem_arena_t*         arena;
    };

    struct eng_asset_t {
        eng_asset_slot_t* slot;
    };

    //-------------------------------------------------------------------
    // MANAGER
    //-------------------------------------------------------------------

    struct eng_asset_mngr_t {
        struct {
            eng_asset_slot_t* text;
            eng_asset_slot_t* image;
            eng_asset_slot_t* sound;
            eng_asset_slot_t* font;
        } slot_list;
        eng_asset_db_t*      db;
        eng_asset_db_file_t* db_file;
    };

    static eng_asset_mngr_t _eng_asset_mngr;

    IFB_ENG_INTERNAL void eng_asset_mngr_startup  (void);
    IFB_ENG_INTERNAL void eng_asset_mngr_shutdown (void);

    //-------------------------------------------------------------------
    // DATABASE
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void eng_asset_db_create     (void);
    IFB_ENG_INTERNAL void eng_asset_db_destroy    (void);
    IFB_ENG_INTERNAL void eng_asset_db_validate   (void);
    IFB_ENG_INTERNAL bool eng_asset_db_load_text  (eng_asset_db_record_t& record);
    IFB_ENG_INTERNAL bool eng_asset_db_load_image (eng_asset_db_record_t& record);
    IFB_ENG_INTERNAL bool eng_asset_db_load_sound (eng_asset_db_record_t& record);
    IFB_ENG_INTERNAL bool eng_asset_db_load_font  (eng_asset_db_record_t& record);

    struct eng_asset_db_table_t {
        u32   row_count;
        pad32 pad;
        struct {
            eng_asset_u32_id_t* id;
            u32*            size;
            u64*            offset;
            u64*            handle;
        } col;
    };

    struct eng_asset_db_record_t {
        eng_asset_u32_id_t  id;
        u32             index;
        u32             size;
        u64             offset;
        u64             handle;
    };

    struct eng_asset_db_t {
        eng_mem_arena_t* arena;
        struct {
            eng_asset_db_table_t* text;
            eng_asset_db_table_t* image;
            eng_asset_db_table_t* sound;
            eng_asset_db_table_t* font;
        } table;
    };

    //-------------------------------------------------------------------
    // DATABASE FILE
    //-------------------------------------------------------------------

    struct eng_asset_db_file_index_t {
        u32 type;
        u32 count;
        u64 start;
        u64 size;
    };

    struct eng_asset_db_file_verif_t {
        cchar* data;
        u64    length;
    };

    struct eng_asset_db_file_t {
        file_h32_t             handle;
        u32                        index_count;
        eng_asset_db_file_index_t* index_array;
        u64                        size;
        eng_asset_db_file_verif_t  verif;
        eng_hash128_t*             hash;
        file_buffer_t          header_buffer;
        eng_mem_arena_t*           arena;
    };

    struct eng_asset_db_builder_t {
        file_h32_t config_file_handle;
    };

    //-------------------------------------------------------------------
    // CONFIG
    //-------------------------------------------------------------------

    struct eng_asset_config_t {
    };



};

#endif //IFB_ENG_ASSET_INTERNAL_HPP