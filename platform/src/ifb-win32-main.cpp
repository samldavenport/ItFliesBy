#pragma once

#define GLEW_STATIC

#include <ifb-engine.hpp>
#include <ifb-engine-core.hpp>

#include "ifb-win32.hpp"


int WINAPI
wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PWSTR     pCmdLine,
    int       nCmdShow) {

    ifb::eng::context* engine_context = ifb::eng::context_create();

    bool is_running = ifb::eng::context_startup(engine_context);
    assert(is_running);

    while (is_running) {

        is_running &=  ifb::eng::context_update      (engine_context);
        is_running &=  ifb::eng::context_render      (engine_context);
        is_running &= !ifb::eng::context_should_quit (engine_context);
    };

    bool is_shutdown = ifb::eng::context_shutdown(engine_context);
    assert(is_shutdown);

    return(S_OK);
}