#pragma once

#include "ifb-engine-os.hpp"

namespace ifb::eng {



    IFB_ENG_INTERNAL void
    os_manager_window_create_and_show(
        os_context* os_mngr) {

        assert(
            os_mngr                != NULL &&
            os_mngr->window        != NULL &&
            os_mngr->monitor_table != NULL &&
        );


    }

};