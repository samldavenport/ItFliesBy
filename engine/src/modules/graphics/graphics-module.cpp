#pragma once

#include "graphics-module.hpp"
#include "memory.hpp"

namespace ifb::eng {

    static graphics_module* _graphics;

    IFB_ENG_INTERNAL graphics_module*
    graphics_module_init(
        void) {

        
        _graphics       = singleton_stack_alloc_struct<graphics_module>();
        auto hello_quad = singleton_stack_alloc_struct<graphics_renderer>();
    
        bool did_alloc = true;
        did_alloc &= (_graphics  != NULL); 
        did_alloc &= (hello_quad != NULL);
        assert(did_alloc);

        _graphics->hello_quad_renderer = hello_quad;

        return(_graphics); 
    }

    IFB_ENG_INTERNAL void
    graphics_module_startup(
        void) {

        assert(_graphics);

        graphics_renderer_create_hello_quad(_graphics->hello_quad_renderer);
    }

    IFB_ENG_INTERNAL void
    graphics_module_shutdown(
        void) {

        assert(_graphics);

        // destroy shader programs
        graphics_renderer_destroy(_graphics->hello_quad_renderer);
    }

    IFB_ENG_INTERNAL void
    graphics_module_render_hello_quad(
        void) {

        assert(_graphics);

        graphics_vertex_buffer vertex_buffer;
        vertex_buffer.size = sizeof(GRAPHICS_QUAD_VERTEX_DATA);
        vertex_buffer.data = (byte*)GRAPHICS_QUAD_VERTEX_DATA;

        graphics_index_buffer index_buffer;
        index_buffer.array = (u32*)GRAPHICS_QUAD_INDEX_DATA;
        index_buffer.count = 6;

        graphics_renderer_draw_buffers(
            _graphics->hello_quad_renderer,
            vertex_buffer,
            index_buffer
        );
    }

};