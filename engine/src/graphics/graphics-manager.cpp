#pragma once

#include "graphics.hpp"

namespace ifb::eng {


    IFB_ENG_INTERNAL graphics_manager*
    graphics_manager_alloc(
        stack& stack) {

        stack.assert_valid();

        auto mngr       = stack.push_struct<graphics_manager>();
        auto hello_quad = stack.push_struct<graphics_renderer>();
    
        bool did_alloc = true;
        did_alloc &= (mngr       != NULL); 
        did_alloc &= (hello_quad != NULL);
        assert(did_alloc);

        mngr->hello_quad_renderer = hello_quad;

        return(mngr);         
    }

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

        assert(graphics && graphics->hello_quad_renderer);
        graphics_renderer* renderer = graphics->hello_quad_renderer;

        gl_context_set_program            (renderer->program);
        gl_context_set_vertex             (renderer->vertex);
        gl_context_set_vertex_buffer      (renderer->buffer.vertex);
        gl_context_set_index_buffer       (renderer->buffer.index);
        
        gl_context_set_vertex_buffer_data ((byte*)GRAPHICS_QUAD_VERTEX_DATA, sizeof(GRAPHICS_QUAD_VERTEX_DATA));
        gl_context_set_index_buffer_data  (GRAPHICS_QUAD_INDEX_DATA,  sizeof(GRAPHICS_QUAD_INDEX_DATA));

        gl_context_render();
        gl_context_reset();
    }

};