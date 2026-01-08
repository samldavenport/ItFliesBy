#pragma once

#include "tables.hpp"


namespace ifb::eng {


    static void
    entity_table_insert(
        entity_table* const in_table,
        const u32           in_count,
        const cchar**       in_tag_cstr,
        entity_id*          out_id) {

        // check args
        table_base_validate((const table_base*)in_table);
        bool can_insert = true;
        can_insert &= (in_table    != NULL);
        can_insert &= (in_count    != 0);
        can_insert &= (in_tag_cstr != NULL);
        can_insert &= (out_id      != NULL);
        assert(can_insert);

        for (
            u32 entity_index = 0;
                entity_index < in_count;
              ++entity_index) {

            
            
        }
    }

    static void
    entity_table_lookup(
        entity_table* const in_table,
        const u32           in_count,
        const entity_id*    in_id,
        entity*             out_entity) {

    }

    static void
    entity_table_delete(
        entity_table* const in_table,
        const u32           in_count,
        const entity_id*    in_id) {

    }
};