#pragma once

#include "os.hpp"
#include "context.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    os_monitor_refresh_table(
        void) {

        os_manager* os = context_get_os_manager();
        os_monitor_table* monitor_table = (os != NULL)
            ? os->monitor_table
            : NULL;
        assert(monitor_table);

        const os_monitor_handle primary_handle = sld::os_monitor_get_primary();
        monitor_table->primary = OS_MONITOR_INVALID;
        monitor_table->count   = sld::os_monitor_count();
        assert(monitor_table->count <= OS_MONITOR_MAX_COUNT);

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

    IFB_ENG_INTERNAL const os_monitor
    os_monitor_get_primary(
        void) {

        os_manager* os = context_get_os_manager();
        os_monitor_table* tbl = (os != NULL) ? os->monitor_table : NULL;
        bool is_valid = (
            tbl          != NULL       &&
            tbl->primary <= tbl->count &&
            tbl->count   <= OS_MONITOR_MAX_COUNT
        );
        assert(is_valid);

        return(tbl->primary);
    }

    IFB_ENG_INTERNAL const os_monitor_handle&
    os_monitor_get_handle(
        const os_monitor monitor) {

        os_manager* os = context_get_os_manager();
        
        const os_monitor_table* tbl = (os != NULL)
            ? os->monitor_table
            : NULL;
        
        assert(
            tbl                != NULL &&
            tbl->array.handles != NULL &&
            monitor            < tbl->count
        );

        const os_monitor_handle& hnd = tbl->array.handles[monitor];
        return(hnd);
    }

    IFB_ENG_INTERNAL const os_monitor_dimensions&
    os_monitor_get_dimensions(
        const os_monitor monitor) {

        os_manager* os = context_get_os_manager();

        const os_monitor_table* tbl = (os != NULL)
            ? os->monitor_table
            : NULL;
        
        assert(
            tbl                   != NULL &&
            tbl->array.dimensions != NULL &&
            monitor               < tbl->count
        );

        const os_monitor_dimensions& dims = tbl->array.dimensions[monitor];
        return(dims);
    }

    IFB_ENG_INTERNAL const os_monitor_name&
    os_monitor_get_name(
        const os_monitor monitor) {

        os_manager* os = context_get_os_manager();

        const os_monitor_table* tbl = (os != NULL)
            ? os->monitor_table
            : NULL;
        
        assert(
            tbl              != NULL &&
            tbl->array.names != NULL &&
            monitor          <  tbl->count
        );

        const os_monitor_name& name = tbl->array.names[monitor];
        return(name);
    }

    IFB_ENG_INTERNAL const u32
    os_monitor_get_center_x(
        const os_monitor_dimensions& dimensions) {

        const u32 center_x = dimensions.virtual_position_x + (dimensions.pixel_width / 2);
        return(center_x);
    }

    IFB_ENG_INTERNAL const u32
    os_monitor_get_center_y(
        const os_monitor_dimensions& dimensions) {

        const u32 center_y = dimensions.virtual_position_y + (dimensions.pixel_height / 2);
        return(center_y);
    }


};