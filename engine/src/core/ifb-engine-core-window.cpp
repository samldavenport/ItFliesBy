#include "ifb-engine-core-internal.hpp"
#include <sld.hpp>
#include <sld-arena.hpp>

#define window_has_event_key_down()             (_eng_core_window.update.events.val & sld::os_window_event_e_key_down)
#define window_has_event_key_up()               (_eng_core_window.update.events.val & sld::os_window_event_e_key_up)
#define window_keyboard_count_keys_down()       _eng_core_input_keyboard.key_count.down
#define window_keyboard_count_keys_up()         _eng_core_input_keyboard.key_count.up
#define window_keyboard_get_keycode_down(index) _eng_core_input_keyboard.keycode_array.down[index]; 
#define window_keyboard_get_keycode_up(index)   _eng_core_input_keyboard.keycode_array.up[index]; 
#define window_keyboard_reset()                 sld::input_keyboard_reset(_eng_core_window.update.keyboard)

namespace ifb {
 
    IFB_ENG_INTERNAL void
    eng_core_window_init(
        void) {

        // set the default dimensions
        _eng_core_window.size.width  = ENG_CORE_WINDOW_DEFAULT_WIDTH;
        _eng_core_window.size.height = ENG_CORE_WINDOW_DEFAULT_HEIGHT;
        _eng_core_window.position.x  = ENG_CORE_WINDOW_DEFAULT_SCREEN_X;
        _eng_core_window.position.y  = ENG_CORE_WINDOW_DEFAULT_SCREEN_Y;

    }

    IFB_ENG_INTERNAL void
    eng_core_window_open_and_show(
        void) {

        sld::color_u32_t clear_color;
        clear_color.r = 0x28;
        clear_color.g = 0x28;
        clear_color.b = 0x28;
        clear_color.a = 1.0f;

        // open the window
        _eng_core_window.last_error = sld::os_window_create(
            _eng_core_window.handle,
            ENG_CORE_WINDOW_TITLE,
            _eng_core_window.size,
            _eng_core_window.position
        );

        // intialize the viewport
        sld::os_window_set_clear_color (_eng_core_window.handle, clear_color);
        sld::os_window_set_viewport    (_eng_core_window.handle, _eng_core_window.size, _eng_core_window.position);

        // show the window
        sld::os_window_show(_eng_core_window.handle);
    }

    IFB_ENG_INTERNAL void
    eng_core_window_process_events(
        void) {

        // get the window update
        _eng_core_window.last_error = sld::os_window_update(
            _eng_core_window.handle,
            _eng_core_window.update
        );


    }

    IFB_ENG_INTERNAL void
    eng_core_window_swap_buffers(
        void) {

        _eng_core_window.last_error = sld::os_window_swap_buffers(_eng_core_window.handle);
    }

    IFB_ENG_INTERNAL void
    eng_core_window_center_to_monitor(
        const eng_core_monitor_handle_t monitor) {

        dims_u32_size_t monitor_size;
        dims_u32_pos_t  monitor_center;
        dims_u32_pos_t  window_center;

        const bool should_reset_window = (_eng_core_window.size.width == 0 || _eng_core_window.size.height == 0); 
        if (should_reset_window) {
            _eng_core_window.size.width  = ENG_CORE_WINDOW_DEFAULT_WIDTH;
            _eng_core_window.size.height = ENG_CORE_WINDOW_DEFAULT_HEIGHT;
        }

        eng_core_monitor_get_size      (monitor,               monitor_size);
        sld::dims_u32_center_a_inside_b(_eng_core_window.size, monitor_size, _eng_core_window.position);
    }

    IFB_ENG_INTERNAL void
    eng_core_window_center_to_primary_monitor(
        void) {

        const bool should_reset_window = (_eng_core_window.size.width == 0 || _eng_core_window.size.height == 0); 
        if (should_reset_window) {
            _eng_core_window.size.width  = ENG_CORE_WINDOW_DEFAULT_WIDTH;
            _eng_core_window.size.height = ENG_CORE_WINDOW_DEFAULT_HEIGHT;
        }

        dims_u32_size_t monitor_size;
        eng_core_monitor_get_size       (_eng_core_monitor_table.monitor_primary,  monitor_size);
        sld::dims_u32_center_a_inside_b (_eng_core_window.size, monitor_size, _eng_core_window.position);
    }

    IFB_ENG_INTERNAL const cchar*
    eng_core_window_open_file_dialog(
        const cchar* path) {

        static sld::os_window_dialog_t dialog;
        dialog.did_select           = false;
        dialog.path_buffer_start    = NULL;
        dialog.path_buffer_selected = _eng_core_file_dialog_selection_buffer;
        dialog.path_size_start      = 0;
        dialog.path_size_selected   = ENG_CORE_FILE_DIALOG_SELECTION_BUFFER_SIZE;

        sld::os_window_open_file_dialog(
            _eng_core_window.handle,
            dialog            
        );

        const cchar* selection = (dialog.did_select)
            ? dialog.path_buffer_selected
            : NULL;

        return(selection);
    }
};