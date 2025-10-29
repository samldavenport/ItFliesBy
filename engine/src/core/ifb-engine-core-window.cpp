#include "ifb-engine-core-window.hpp"

#define window_has_event_key_down()             (_window.update.events.val & sld::os_window_event_e_key_down)
#define window_has_event_key_up()               (_window.update.events.val & sld::os_window_event_e_key_up)
#define window_keyboard_count_keys_down()       _eng_core_input_keyboard.key_count.down
#define window_keyboard_count_keys_up()         _eng_core_input_keyboard.key_count.up
#define window_keyboard_get_keycode_down(index) _eng_core_input_keyboard.keycode_array.down[index]; 
#define window_keyboard_get_keycode_up(index)   _eng_core_input_keyboard.keycode_array.up[index]; 
#define window_keyboard_reset()                 sld::input_keyboard_reset(_window.update.keyboard)

namespace ifb::eng {
 
    //-------------------------------------------------------------------
    // GLOBALS
    //-------------------------------------------------------------------

    IFB_ENG_GLOBAL core_window_t                       _window;
    IFB_ENG_GLOBAL core_window_file_dialog_selection_t _dialog_selection;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void
    core_window_init(
        void) {

        // set the default dimensions
        _window.size.width  = CORE_WINDOW_DEFAULT_WIDTH;
        _window.size.height = CORE_WINDOW_DEFAULT_HEIGHT;
        _window.position.x  = CORE_WINDOW_DEFAULT_SCREEN_X;
        _window.position.y  = CORE_WINDOW_DEFAULT_SCREEN_Y;
    }

    IFB_ENG_INTERNAL void
    core_window_open_and_show(
        void) {

        sld::color_u32_t clear_color;
        clear_color.r = 0x28;
        clear_color.g = 0x28;
        clear_color.b = 0x28;
        clear_color.a = 1.0f;

        // open the window
        _window.last_error = sld::os_window_create(
            _window.handle,
            CORE_WINDOW_TITLE,
            _window.size,
            _window.position
        );

        // intialize the viewport
        sld::os_window_set_clear_color (_window.handle, clear_color);
        sld::os_window_set_viewport    (_window.handle, _window.size, _window.position);

        // show the window
        sld::os_window_show(_window.handle);
    }

    IFB_ENG_INTERNAL void
    core_window_process_events(
        void) {

        // get the window update
        _window.last_error = sld::os_window_update(
            _window.handle,
            _window.update
        );
    }

    IFB_ENG_INTERNAL void
    core_window_swap_buffers(
        void) {

        _window.last_error = sld::os_window_swap_buffers(_window.handle);
    }

    IFB_ENG_INTERNAL void
    core_window_center_to_monitor(
        const core_monitor_index_t monitor_index) {

        const bool should_reset_window = (_window.size.width == 0 || _window.size.height == 0); 
        if (should_reset_window) {
            _window.size.width  = CORE_WINDOW_DEFAULT_WIDTH;
            _window.size.height = CORE_WINDOW_DEFAULT_HEIGHT;
        }

        const core_monitor_size_t& monitor_size = core_monitor_get_size(monitor_index);
        sld::dims_u32_center_a_inside_b(_window.size, monitor_size, _window.position);
    }

    IFB_ENG_INTERNAL void
    core_window_center_to_primary_monitor(
        void) {

        const bool should_reset_window = (_window.size.width == 0 || _window.size.height == 0); 
        if (should_reset_window) {
            _window.size.width  = CORE_WINDOW_DEFAULT_WIDTH;
            _window.size.height = CORE_WINDOW_DEFAULT_HEIGHT;
        }

        const core_monitor_size_t& monitor_size = core_monitor_get_primary_size();
        sld::dims_u32_center_a_inside_b (_window.size, monitor_size, _window.position);
    }

    IFB_ENG_INTERNAL const cchar*
    core_window_open_file_dialog(
        const core_window_file_dialog_t& file_dialog) {

        static sld::os_window_dialog_t dialog;
        dialog.filter                 = file_dialog.filter;
        dialog.start                  = file_dialog.starting_path;
        dialog.title                  = file_dialog.title; 
        dialog.selection_buffer_cstr  = _dialog_selection.buffer;
        dialog.selection_buffer_size  = CORE_WINDOW_FILE_DIALOG_SELECTION_BUFFER_SIZE;
        dialog.did_select             = false;

        sld::os_window_open_file_dialog(
            _window.handle,
            dialog            
        );

        const cchar* selection = (dialog.did_select)
            ? dialog.selection_buffer_cstr
            : NULL;

        return(selection);
    }
    
    IFB_ENG_INTERNAL const cchar*
    core_window_save_file_dialog(
        const core_window_file_dialog_t& file_dialog) {

        static sld::os_window_dialog_t dialog;
        dialog.filter                 = file_dialog.filter;
        dialog.start                  = file_dialog.starting_path;
        dialog.title                  = file_dialog.title; 
        dialog.selection_buffer_cstr  = _dialog_selection.buffer;
        dialog.selection_buffer_size  = CORE_WINDOW_FILE_DIALOG_SELECTION_BUFFER_SIZE;
        dialog.did_select             = false;

        sld::os_window_save_file_dialog(
            _window.handle,
            dialog            
        );

        const cchar* selection = (dialog.did_select)
            ? dialog.selection_buffer_cstr
            : NULL;

        return(selection);
    }

    IFB_ENG_INTERNAL const core_window_update_t&
    core_window_get_update(
        void) {

        return(_window.update);
    }

    IFB_ENG_INTERNAL bool
    core_window_quit_received(
        void) {

        return(_window.update.events.val & sld::os_window_event_e_quit);
    }
};