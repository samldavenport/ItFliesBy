#ifndef IFB_ENG_ASSET_INTERNAL_HPP
#define IFB_ENG_ASSET_INTERNAL_HPP

#include <sld-xml.hpp>
#include <sld-memory.hpp>
#include <sld-block-allocator.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-hash.hpp"
#include "ifb-engine-asset.hpp"
#include "ifb-engine-file.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct asset_block_alctr_t : block_allocator_t { };
    struct asset_block_t;
    struct asset_slot_t;
    struct asset_mngr_t;
    struct asset_db_t;
    struct asset_db_table_t;
    struct asset_db_builder_t;
    struct asset_db_record_t;
    struct asset_db_t;
    struct asset_db_file_index_t;
    struct asset_db_file_verif_t;
    struct asset_db_file_header_t;
    struct asset_db_file_t;
    struct asset_db_builder_t;

    //-------------------------------------------------------------------
    // ASSET
    //-------------------------------------------------------------------

    struct asset_slot_t {
        asset_block_alctr_t* alctr;
        asset_slot_t*        next;
        asset_slot_t*        prev;
        arena_t*             arena;
    };

    struct asset_t {
        asset_slot_t* slot;
    };

    //-------------------------------------------------------------------
    // MANAGER
    //-------------------------------------------------------------------

    struct asset_mngr_t {
        struct {
            asset_slot_t* text;
            asset_slot_t* image;
            asset_slot_t* sound;
            asset_slot_t* font;
        } slot_list;
        asset_db_t*      db;
        asset_db_file_t* db_file;
    };

    static asset_mngr_t _eng_asset_mngr;

    IFB_ENG_INTERNAL void eng_asset_mngr_startup  (void);
    IFB_ENG_INTERNAL void eng_asset_mngr_shutdown (void);

    //-------------------------------------------------------------------
    // DATABASE
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void asset_db_create     (void);
    IFB_ENG_INTERNAL void asset_db_destroy    (void);
    IFB_ENG_INTERNAL void asset_db_validate   (void);
    IFB_ENG_INTERNAL bool asset_db_load_text  (asset_db_record_t& record);
    IFB_ENG_INTERNAL bool asset_db_load_image (asset_db_record_t& record);
    IFB_ENG_INTERNAL bool asset_db_load_sound (asset_db_record_t& record);
    IFB_ENG_INTERNAL bool asset_db_load_font  (asset_db_record_t& record);

    struct asset_db_table_t {
        u32   row_count;
        pad32 pad;
        struct {
            asset_id_t* id;
            u32*        size;
            u64*        offset;
            u64*        handle;
        } col;
    };

    struct asset_db_record_t {
        asset_id_t id;
        u32        index;
        u32        size;
        u64        offset;
        u64        handle;
    };

    struct asset_db_t {
        arena_t* arena;
        struct {
            asset_db_table_t* text;
            asset_db_table_t* image;
            asset_db_table_t* sound;
            asset_db_table_t* font;
        } table;
    };

    //-------------------------------------------------------------------
    // DATABASE FILE
    //-------------------------------------------------------------------

    struct asset_db_file_index_t {
        u32 type;
        u32 count;
        u64 start;
        u64 size;
    };

    struct asset_db_file_verif_t {
        cchar* data;
        u64    length;
    };

    struct asset_db_file_t {
        file_t                 handle;
        u32                    index_count;
        asset_db_file_index_t* index_array;
        u64                    size;
        asset_db_file_verif_t  verif;
        hash128_t*             hash;
        file_buffer_t          header_buffer;
        arena_t*               arena;
    };

    struct asset_db_builder_t {
        file_t config_file_handle;
    };

    //-------------------------------------------------------------------
    // CONFIG
    //-------------------------------------------------------------------

    struct asset_config_t {
    };



};

#endif //IFB_ENG_ASSET_INTERNAL_HPP