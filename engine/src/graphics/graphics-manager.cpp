#pragma once

#include "graphics.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    graphics_manager_startup(
        graphics_manager* graphics) {

        assert(graphics);

        graphics_renderer_create_hello_quad(graphics->hello_quad_renderer);
    }

    IFB_ENG_INTERNAL void
    graphics_manager_shutdown(
        graphics_manager* graphics) {

        assert(graphics);

        // destroy shader programs
        graphics_renderer_destroy(graphics->hello_quad_renderer);
    }

    IFB_ENG_INTERNAL void
    graphics_manager_render_hello_quad(
        graphics_manager* graphics) {

        assert(graphics);

        graphics_vertex_buffer vertex_buffer;
        vertex_buffer.size = sizeof(GRAPHICS_QUAD_VERTEX_DATA);
        vertex_buffer.data = (byte*)GRAPHICS_QUAD_VERTEX_DATA;

        graphics_index_buffer index_buffer;
        index_buffer.array = (u32*)GRAPHICS_QUAD_INDEX_DATA;
        index_buffer.count = 6;

        graphics_renderer_draw_buffers(
            graphics->hello_quad_renderer,
            vertex_buffer,
            index_buffer
        );
    }

};