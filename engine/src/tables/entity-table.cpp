#pragma once

#include "tables.hpp"

namespace ifb::eng {

    static void
    entity_table_insert(
        const u32         in_count,
        const entity_tag* in_tag,
        entity_id*        out_id) {

    }

    static void
    entity_table_lookup(
        const u32         in_count,
        const entity_id*  in_id,
        entity*           out_entity) {

    }

    static void
    entity_table_delete(
        const u32        in_count,
        const entity_id* in_id) {

    }
};