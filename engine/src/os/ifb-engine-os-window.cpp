#pragma once

#include "ifb-engine-os.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    os_window_create_and_show(
        os_context* os) {

        assert(
            os         != NULL &&
            os->window != NULL
        );
        os_window* window = os->window;
        
        // get monitor dimensions
        const os_monitor_dimensions* monitor_dims = os_monitor_get_primrary_dimensions(os);
        assert(monitor_dims != NULL);


        // configure window 
        os_window_config config;
        config.position.x  = monitor_dims->virtual_position_x + (monitor_dims->pixel_width  / 2);
        config.position.y  = monitor_dims->virtual_position_y + (monitor_dims->pixel_height / 2);
        config.size.width  = 1024;
        config.size.height = 768;
        config.title       = "It Flies By";

        // create window handle and show window        
        window->handle = os_window_create(&config);
        assert(window->handle != NULL);
        assert(os_window_show(window->handle));

        

    }
};