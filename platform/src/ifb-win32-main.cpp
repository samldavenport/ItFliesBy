#pragma once

#define GLEW_STATIC

#include <ifb-engine.hpp>
#include <ifb-engine-core.hpp>

#include "ifb-win32.hpp"

constexpr u32  reservation_size = size_megabytes(64);
constexpr u32  stack_size       = size_kilobytes(64);
static    byte stack_memory[stack_size];

int WINAPI
wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PWSTR     pCmdLine,
    int       nCmdShow) {

    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);

    ifb::eng::engine_config config;

    // initialize memory map
    auto& mem_map_singleton_stack = config.mem_map.singleton_stack;
    auto& mem_map_vmem            = config.mem_map.os_virtual_memory;
    mem_map_singleton_stack.init(stack_memory, stack_size);
    mem_map_vmem.page_size                         = sys_info.dwPageSize;
    mem_map_vmem.granularity                       = sys_info.dwAllocationGranularity;
    mem_map_vmem.reservation.arenas.start.as_ptr   = VirtualAlloc(NULL, reservation_size, MEM_RESERVE, PAGE_READONLY);
    mem_map_vmem.reservation.entities.start.as_ptr = VirtualAlloc(NULL, reservation_size, MEM_RESERVE, PAGE_READONLY);
    mem_map_vmem.reservation.graphics.start.as_ptr = VirtualAlloc(NULL, reservation_size, MEM_RESERVE, PAGE_READONLY);
    mem_map_vmem.reservation.arenas.size           = reservation_size;
    mem_map_vmem.reservation.entities.size         = reservation_size;
    mem_map_vmem.reservation.graphics.size         = reservation_size;

    ifb::eng::context* engine_context = ifb::eng::context_create(config);

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