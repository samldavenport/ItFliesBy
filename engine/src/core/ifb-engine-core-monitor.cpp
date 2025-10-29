#include <stdio.h>

#include "ifb-engine-core-monitor.hpp"
namespace ifb::eng {

    IFB_ENG_GLOBAL core_monitor_table_t     _table;
    IFB_ENG_GLOBAL core_monitor_pos_t       _array_pos    [ENG_CORE_MONITOR_COUNT_MAX];
    IFB_ENG_GLOBAL core_monitor_size_t      _array_size   [ENG_CORE_MONITOR_COUNT_MAX];
    IFB_ENG_GLOBAL core_monitor_name_t      _array_name   [ENG_CORE_MONITOR_COUNT_MAX];
    IFB_ENG_GLOBAL core_monitor_os_handle_t _array_handle [ENG_CORE_MONITOR_COUNT_MAX];
    IFB_ENG_GLOBAL cchar                    _name_buffer  [ENG_CORE_MONITOR_NAME_BUFFER_SIZE];

    IFB_ENG_INTERNAL bool
    core_monitor_table_validate(
        void) {

        //TODO(SAM): active handle
        bool is_valid = true;
        is_valid &= (_table.monitor_primary.val          <  ENG_CORE_MONITOR_INDEX_INVALID);
        is_valid &= (_table.monitor_count                != 0);
        is_valid &= (_table.monitor_virtual_size.width   != 0);
        is_valid &= (_table.monitor_virtual_size.height  != 0);
        is_valid &= (_table.array.position               != NULL);
        is_valid &= (_table.array.size                   != NULL);
        is_valid &= (_table.array.name                   != NULL);
        is_valid &= (_table.array.handle                 != NULL);
        return(is_valid);
    }

    IFB_ENG_INTERNAL void
    core_monitor_table_assert_valid(
        void) {

        assert(core_monitor_table_validate());
    }

    IFB_ENG_INTERNAL void
    core_monitor_table_init(
        void) {

        static bool is_init = false;
        assert(!is_init);

        // initialize names
        for (
            u32 index = 0;
            index < ENG_CORE_MONITOR_COUNT_MAX;
            ++index) {

            const u32 buffer_offset   = (index * ENG_CORE_MONITOR_NAME_LENGTH);
            _array_name[index].buffer = &_name_buffer[buffer_offset];
        }

        _table.monitor_primary.val         = 0;
        _table.monitor_active.val          = 0;
        _table.monitor_count               = 0;
        _table.monitor_virtual_size.width  = 0;
        _table.monitor_virtual_size.height = 0;
        _table.array.position              = _array_pos; 
        _table.array.size                  = _array_size; 
        _table.array.name                  = _array_name; 
        _table.array.handle                = _array_handle; 

        // do the first refresh and assert valid
        core_monitor_table_refresh();     
        core_monitor_table_assert_valid();
        is_init = true;
    }

    IFB_ENG_INTERNAL void
    core_monitor_table_refresh(
        void) {

        // get the monitor info and working area
        sld::os_monitor_working_area_t working_area;
        sld::os_monitor_info_t         info_array[ENG_CORE_MONITOR_COUNT_MAX];
        sld::os_monitor_working_area   (working_area);
        sld::os_monitor_info           (info_array);
        sld::os_monitor_handle_t primary_handle = sld::os_monitor_primary (); 

        // update the table
        _table.monitor_count               = sld::os_monitor_count   ();
        _table.monitor_virtual_size.width  = working_area.virtual_pixel_height;
        _table.monitor_virtual_size.height = working_area.virtual_pixel_width;
        _table.monitor_active.val          = ENG_CORE_MONITOR_INDEX_INVALID;
        _table.monitor_primary.val         = ENG_CORE_MONITOR_INDEX_INVALID;


        // add the monitors to the table
        cstr_t monitor_name_cstr_src = { NULL, sld::OS_MONITOR_NAME_WIDTH};
        cstr_t monitor_name_cstr_dst = { NULL, sld::OS_MONITOR_NAME_WIDTH};
        for (
            u32 monitor = 0;
                monitor < _table.monitor_count;
              ++monitor) {

            // get the next info
            sld::os_monitor_info_t& info = info_array[monitor];

            // check the monitor is valid
            bool is_monitor_valid = true;
            is_monitor_valid = (info.handle.val   != NULL);
            is_monitor_valid = (info.index        < _table.monitor_count);
            is_monitor_valid = (info.pixel_width  > 0);
            is_monitor_valid = (info.pixel_height > 0);
            is_monitor_valid = (info.pixel_width  <= working_area.virtual_pixel_width);
            is_monitor_valid = (info.pixel_height <= working_area.virtual_pixel_height);
            is_monitor_valid = (info.position_x   <= working_area.virtual_pixel_width);
            is_monitor_valid = (info.position_y   <= working_area.virtual_pixel_height);
            assert(is_monitor_valid);

            if (info.handle.val == primary_handle.val) {
                _table.monitor_primary.val = monitor;
            }

            // copy the name
            cchar* name_cstr = _table.array.name[monitor].buffer;
            sprintf_s(
                name_cstr,
                sld::OS_MONITOR_NAME_WIDTH,
                "%s", info.name_cstr
            );


            // set remaining properties
            _table.array.position [monitor].x      = info.position_x;    
            _table.array.position [monitor].y      = info.position_y;    
            _table.array.size     [monitor].width  = info.pixel_width;    
            _table.array.size     [monitor].height = info.pixel_height;    
            _table.array.handle   [monitor]        = info.handle;
        }

        // check the properties
        bool is_valid = true;
        is_valid &= core_monitor_table_validate();
        is_valid &= (_table.monitor_primary.val < ENG_CORE_MONITOR_INDEX_INVALID); 
        assert(is_valid);        
    }

    IFB_ENG_INTERNAL u32
    core_monitor_table_get_count(
        void) {

        core_monitor_table_assert_valid();
        return(_table.monitor_count);
    }

    IFB_ENG_INTERNAL const core_monitor_index_t
    core_monitor_get_index_from_handle(
        const core_monitor_os_handle_t handle) {

        core_monitor_table_assert_valid();

        core_monitor_index_t index;
        bool found = false;
        for (
            index.val = 0;
            index.val < _table.monitor_count;
            ++index.val) {

            if (_table.array.handle[index.val].val == handle.val) {
                found = true;
                break;
            }
        }

        assert(found);
        return(index);
    }

    IFB_ENG_INTERNAL const core_monitor_size_t&
    core_monitor_get_primary_size(
        void) {

        core_monitor_table_assert_valid();

        const u32 index = _table.monitor_primary.val;
        return(_table.array.size[index]);
    }

    IFB_ENG_INTERNAL const core_monitor_pos_t&
    core_monitor_get_primary_position(
        void) {

        core_monitor_table_assert_valid();

        const u32 index = _table.monitor_primary.val;
        return(_table.array.position[index]);
    }

    IFB_ENG_INTERNAL const core_monitor_name_t&
    core_monitor_get_primary_name(
        void) {

        core_monitor_table_assert_valid();

        const u32 index = _table.monitor_primary.val;
        return(_table.array.name[index]);
    }

    IFB_ENG_INTERNAL const core_monitor_os_handle_t&
    core_monitor_get_primary_handle(
        void) {

        core_monitor_table_assert_valid();

        const u32 index = _table.monitor_primary.val;
        return(_table.array.handle[index]);
    }


    IFB_ENG_INTERNAL const core_monitor_size_t&
    core_monitor_get_size(
        const core_monitor_index_t index) {

        bool is_valid = true; 
        is_valid &= core_monitor_table_validate();
        is_valid &= (index.val < _table.monitor_count);
        assert(is_valid);

        return(_table.array.size[index.val]);
    }

    IFB_ENG_INTERNAL const core_monitor_pos_t&
    core_monitor_get_position(
        const core_monitor_index_t index) {

        bool is_valid = true; 
        is_valid &= core_monitor_table_validate();
        is_valid &= (index.val < _table.monitor_count);
        assert(is_valid);

        return(_table.array.position[index.val]);
    }

    IFB_ENG_INTERNAL const core_monitor_name_t&
    core_monitor_get_name(
        const core_monitor_index_t index) {

        bool is_valid = true; 
        is_valid &= core_monitor_table_validate();
        is_valid &= (index.val < _table.monitor_count);
        assert(is_valid);

        return(_table.array.name[index.val]);
    }

    IFB_ENG_INTERNAL const core_monitor_os_handle_t&
    core_monitor_get_handle(
        const core_monitor_index_t index) {

        bool is_valid = true; 
        is_valid &= core_monitor_table_validate();
        is_valid &= (index.val < _table.monitor_count);
        assert(is_valid);

        return(_table.array.handle[index.val]);
    }
};