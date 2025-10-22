#include "ifb-engine-core-internal.hpp"

namespace ifb {

    IFB_ENG_INTERNAL bool
    eng_core_monitor_table_validate(
        void) {

        //TODO(SAM): primary and active handles
        bool is_valid = true;
        is_valid &= (_eng_core_monitor_table.monitor_count                != 0);
        is_valid &= (_eng_core_monitor_table.monitor_virtual_size.width   != 0);
        is_valid &= (_eng_core_monitor_table.monitor_virtual_size.height  != 0);
        is_valid &= (_eng_core_monitor_table.array.position               != NULL);
        is_valid &= (_eng_core_monitor_table.array.size                   != NULL);
        is_valid &= (_eng_core_monitor_table.array.name                   != NULL);
        is_valid &= (_eng_core_monitor_table.array.handle                 != NULL);
        return(is_valid);
    }

    IFB_ENG_INTERNAL void
    eng_core_monitor_table_init(
        void) {

        static bool is_init = false;
        assert(!is_init);

        static eng_core_monitor_pos_t    array_pos    [ENG_CORE_MONITOR_COUNT_MAX];
        static eng_core_monitor_size_t   array_size   [ENG_CORE_MONITOR_COUNT_MAX];
        static eng_core_monitor_name_t   array_name   [ENG_CORE_MONITOR_COUNT_MAX];
        static eng_core_monitor_handle_t array_handle [ENG_CORE_MONITOR_COUNT_MAX];

        _eng_core_monitor_table.monitor_primary.val         = 0;
        _eng_core_monitor_table.monitor_active.val          = 0;
        _eng_core_monitor_table.monitor_count               = 0;
        _eng_core_monitor_table.monitor_virtual_size.width  = 0;
        _eng_core_monitor_table.monitor_virtual_size.height = 0;
        _eng_core_monitor_table.array.position              = array_pos; 
        _eng_core_monitor_table.array.size                  = array_size; 
        _eng_core_monitor_table.array.name                  = array_name; 
        _eng_core_monitor_table.array.handle                = array_handle; 

        // do the first refresh and assert valid
        eng_core_monitor_table_refresh();     
        eng_core_monitor_table_validate();
        is_init = true;
    }

    IFB_ENG_INTERNAL void
    eng_core_monitor_table_refresh(
        void) {

        // get the monitor info and working area
        sld::os_monitor_working_area_t working_area;
        sld::os_monitor_info_t         info_array[ENG_CORE_MONITOR_COUNT_MAX];
        sld::os_monitor_working_area   (working_area);
        sld::os_monitor_info           (info_array);

        // update the table
        _eng_core_monitor_table.monitor_primary             = sld::os_monitor_primary ();
        _eng_core_monitor_table.monitor_count               = sld::os_monitor_count   ();
        _eng_core_monitor_table.monitor_virtual_size.width  = working_area.virtual_pixel_height;
        _eng_core_monitor_table.monitor_virtual_size.height = working_area.virtual_pixel_width;

        // check the properties
        bool is_valid = true;
        is_valid &= eng_core_monitor_table_validate();

        assert(is_valid);        
        
        // add the monitors to the table
        cstr_t monitor_name_cstr_src = { NULL, sld::OS_MONITOR_NAME_WIDTH};
        cstr_t monitor_name_cstr_dst = { NULL, sld::OS_MONITOR_NAME_WIDTH};
        for (
            u32 monitor = 0;
                monitor < _eng_core_monitor_table.monitor_count;
              ++monitor) {

            // get the next info
            sld::os_monitor_info_t& info = info_array[monitor];

            // check the monitor is valid
            bool is_monitor_valid = true;
            is_monitor_valid = (info.handle.val   != NULL);
            is_monitor_valid = (info.index        < _eng_core_monitor_table.monitor_count);
            is_monitor_valid = (info.pixel_width  > 0);
            is_monitor_valid = (info.pixel_height > 0);
            is_monitor_valid = (info.pixel_width  <= working_area.virtual_pixel_width);
            is_monitor_valid = (info.pixel_height <= working_area.virtual_pixel_height);
            is_monitor_valid = (info.position_x   <= working_area.virtual_pixel_width);
            is_monitor_valid = (info.position_y   <= working_area.virtual_pixel_height);
            assert(is_monitor_valid);

            // copy the name
            const u32 name_str_offset = (monitor * sld::OS_MONITOR_NAME_WIDTH); 
            monitor_name_cstr_src.chars   = &info.name_cstr                           [name_str_offset];
            monitor_name_cstr_dst.chars   = &_eng_core_monitor_table.array.name->cstr [name_str_offset];
            sld::cstr_copy_from(&monitor_name_cstr_dst, monitor_name_cstr_src.chars, monitor_name_cstr_src.size);

            // set remaining properties
            _eng_core_monitor_table.array.position [monitor].x      = info.position_x;    
            _eng_core_monitor_table.array.position [monitor].y      = info.position_y;    
            _eng_core_monitor_table.array.size     [monitor].width  = info.pixel_width;    
            _eng_core_monitor_table.array.size     [monitor].height = info.pixel_height;    
            _eng_core_monitor_table.array.handle   [monitor]        = info.handle;
        }
    }

    IFB_ENG_INTERNAL u32
    eng_core_monitor_table_search(
        const eng_core_monitor_handle_t monitor) {

        bool is_valid = true; 
        is_valid &= eng_core_monitor_table_validate();
        is_valid &= (monitor.val != NULL);
        assert(is_valid);

        u32  index    = 0;
        bool is_found = false;
        for (
              index;
              index < _eng_core_monitor_table.monitor_count;
            ++index) {

            is_found |= (_eng_core_monitor_table.array.handle[index].val == monitor.val);
            if (is_found) break;
        }

        assert(is_found && index < _eng_core_monitor_table.monitor_count);
        return(index);
    }

    IFB_ENG_INTERNAL void
    eng_core_monitor_get_size(
        const eng_core_monitor_handle_t monitor,
        eng_core_monitor_size_t&        size) {

        bool is_valid = true; 
        is_valid &= eng_core_monitor_table_validate();
        is_valid &= (monitor.val != NULL);
        assert(is_valid);

        const u32 index = eng_core_monitor_table_search(monitor);
        size            = _eng_core_monitor_table.array.size[index];
    }

    IFB_ENG_INTERNAL void
    eng_core_monitor_get_position(
        const eng_core_monitor_handle_t monitor,
        eng_core_monitor_pos_t&         pos) {

        bool is_valid = true; 
        is_valid &= eng_core_monitor_table_validate();
        is_valid &= (monitor.val != NULL);
        assert(is_valid);

        const u32 index = eng_core_monitor_table_search(monitor);
        pos             = _eng_core_monitor_table.array.position [index];
    }

    IFB_ENG_INTERNAL void
    eng_core_monitor_get_name(
        const eng_core_monitor_handle_t monitor,
        eng_core_monitor_name_t&           name) {

        bool is_valid = true; 
        is_valid &= eng_core_monitor_table_validate();
        is_valid &= (monitor.val != NULL);
        assert(is_valid);

        const u32 index = eng_core_monitor_table_search(monitor);

        cstr_t dst;
        dst.chars = name.cstr;
        dst.size  = sld::OS_MONITOR_NAME_WIDTH;

        cstr_t src;
        src.chars = _eng_core_monitor_table.array.name[index * sld::OS_MONITOR_NAME_WIDTH].cstr;  
        src.size  = sld::OS_MONITOR_NAME_WIDTH;

        (void)sld::cstr_copy_from(&dst, src.chars, src.size);
    }

    IFB_ENG_INTERNAL void
    eng_core_monitor_get_info(
        const eng_core_monitor_handle_t monitor,
        eng_core_monitor_info_t&           info) {

        bool is_valid = true; 
        is_valid &= eng_core_monitor_table_validate();
        is_valid &= (monitor.val != NULL);
        assert(is_valid);

        const u32 index = eng_core_monitor_table_search(monitor);

        info.size.width  = _eng_core_monitor_table.array.size     [index].width;
        info.size.height = _eng_core_monitor_table.array.size     [index].height;
        info.pos.x       = _eng_core_monitor_table.array.position [index].x;
        info.pos.y       = _eng_core_monitor_table.array.position [index].y;

        cstr_t dst, src;
        dst.chars = info.name.cstr;
        src.chars = _eng_core_monitor_table.array.name[index * sld::OS_MONITOR_NAME_WIDTH].cstr;  
        dst.size  = sld::OS_MONITOR_NAME_WIDTH;
        src.size  = sld::OS_MONITOR_NAME_WIDTH;
        (void)sld::cstr_copy_from(&dst, src.chars, src.size);
    }
};