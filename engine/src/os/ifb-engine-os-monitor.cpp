#pragma once

#include "ifb-engine-os.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    os_monitor_init_table(
        os_context* os) {

        os_monitor_table* monitor_table = (os != NULL)
            ? os->monitor_table
            : NULL;
        assert(monitor_table);

        const os_monitor_handle primary_handle = sld::os_monitor_get_primary();
        monitor_table->primary = OS_MONITOR_INVALID;
        monitor_table->count   = sld::os_monitor_count();
        assert(monitor_table->count <= OS_MAX_COUNT_MONITORS);

        sld::os_monitor_info monitor_info;
        for (
            monitor_info.index = 0;
            monitor_info.index < monitor_table->count;
            ++monitor_info.index) {

            sld::os_monitor_get_info(monitor_info);

            monitor_table->array.dimensions [monitor_info.index] = monitor_info.dimensions;
            monitor_table->array.handles    [monitor_info.index] = monitor_info.handle;
            monitor_table->array.names      [monitor_info.index] = monitor_info.name;

            if (monitor_info.handle == primary_handle) {
                monitor_table->primary = monitor_info.index;
            }
        }

        assert(monitor_table->primary != OS_MONITOR_INVALID);
    }

    IFB_ENG_INTERNAL const os_monitor_dimensions*
    os_monitor_get_primary_dimensions(
        os_context* os) {

        os_monitor_table* monitor_table = (os != NULL)
            ? os->monitor_table
            : NULL;
            
        assert(
            monitor_table                                &&
            monitor_table->primary != OS_MONITOR_INVALID &&
            monitor_table->count   <= OS_MAX_COUNT_MONITORS
        );

        const os_monitor             monitor = monitor_table->primary;
        const os_monitor_dimensions* dims    = &monitor_table->array.dimensions[monitor];

        return(dims);
    }

};