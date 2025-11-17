#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    eng_asset_db_create(
        void) {

        bool can_init = true;
        
    }

    IFB_ENG_INTERNAL void
    eng_asset_db_destroy(
        void) {

    }

    IFB_ENG_INTERNAL void
    eng_asset_db_validate(
        void) {

        bool is_valid = (_eng_asset_mngr.db != NULL);
        if (is_valid) {
            is_valid &= (_eng_asset_mngr.db->table.text  != NULL);
            is_valid &= (_eng_asset_mngr.db->table.image != NULL);
            is_valid &= (_eng_asset_mngr.db->table.sound != NULL);
            is_valid &= (_eng_asset_mngr.db->table.font  != NULL);
        }
        assert(is_valid);
    }

    IFB_ENG_INTERNAL bool
    eng_asset_db_load_text(
        eng_asset_db_t* const  db,
        eng_asset_db_record_t& record) {

    }

    IFB_ENG_INTERNAL bool
    eng_asset_db_load_image(
        eng_asset_db_t* const  db,
        eng_asset_db_record_t& record) {

    }

    IFB_ENG_INTERNAL bool
    eng_asset_db_load_sound(
        eng_asset_db_t* const  db,
        eng_asset_db_record_t& record) {

    }

    IFB_ENG_INTERNAL bool
    eng_asset_db_load_font(
        eng_asset_db_t* const  db,
        eng_asset_db_record_t& record) {

    }
};