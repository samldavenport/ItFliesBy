#pragma once

#include "tables.hpp"
#include "memory.hpp"

namespace ifb::eng {

    struct tables {
        entity_table*    entity;
        transform_table* transform;
    } static _tables;

    static void
    tables_init(
        void) {

        _tables.entity    = memory_stack_alloc_struct<entity_table>();
        _tables.transform = memory_stack_alloc_struct<transform_table>();
    }
};