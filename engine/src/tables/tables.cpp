#pragma once

#include "tables.hpp"
#include "memory.hpp"

namespace ifb::eng {

    static void
    table_base_validate(
        table_base* const table) {

        bool is_valid = (table != NULL);
        if (is_valid) {

            table->index_array.validate();
            table->index_cache.validate();
            is_valid &= (table->count_per_page != 0);
        }
        assert(is_valid);
    }

};