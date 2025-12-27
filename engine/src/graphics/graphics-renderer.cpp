#pragma once

#include "graphics.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    graphics_renderer_create(
        graphics_renderer*                   renderer,
        const cchar*                         shader_src_vertex,
        const cchar*                         shader_src_fragment,
        const u32                            vertex_size,
        const graphics_vertex_property_type* vertex_property_array,
        const u32                            vertex_property_count) {

        bool can_create = true;
        can_create &= (renderer              != NULL);
        can_create &= (shader_src_vertex     != NULL);
        can_create &= (shader_src_fragment   != NULL);
        can_create &= (vertex_property_array != NULL);
        can_create &= (vertex_property_count != 0);
        assert(can_create);

        // initialize the pipeline
        gl_pipeline pipeline;
        gl_pipeline_init(pipeline);

        // compile the shaders
        bool did_compile = true;
        did_compile &= gl_pipeline_compile_shader_vertex   (pipeline, shader_src_vertex);
        did_compile &= gl_pipeline_compile_shader_fragment (pipeline, shader_src_fragment);
        assert(did_compile);

        // create and link program
        gl_program_create(renderer->program);
        const bool did_link = gl_program_link_pipeline(
            renderer->program,
            pipeline
        );
        assert(did_link);

        // clean up pipeline
        gl_pipeline_cleanup(pipeline);

        // create buffers and vertex
        gl_buffer_create             (renderer->buffer.vertex);
        gl_buffer_create             (renderer->buffer.index);
        gl_vertex_create             (renderer->vertex);
        gl_context_set_vertex        (renderer->vertex);
        gl_context_set_vertex_buffer (renderer->buffer.vertex);

        // set the vertex properties
        using vertex_property_method = bool (*)(
            gl_vertex& vertex,
            const u32  vertex_size,
            const u32  attribute_index,
            const u32  attribute_offset
        );
        constexpr vertex_property_method vertex_property_method_array[graphics_vertex_property_type_count] = {
            gl_vertex_attribute_set_s32,  // graphics_vertex_property_s32
            gl_vertex_attribute_set_u32,  // graphics_vertex_property_u32
            gl_vertex_attribute_set_f32,  // graphics_vertex_property_f32
            gl_vertex_attribute_set_vec2, // graphics_vertex_property_vec2
            gl_vertex_attribute_set_vec3  // graphics_vertex_property_vec3
        };
        constexpr u32 vertex_property_size_array[graphics_vertex_property_type_count] = {
            sizeof(s32),  // graphics_vertex_property_s32
            sizeof(u32),  // graphics_vertex_property_u32
            sizeof(f32),  // graphics_vertex_property_f32
            sizeof(vec2), // graphics_vertex_property_vec2
            sizeof(vec3)  // graphics_vertex_property_vec3
        };

        u32 offset = 0;
        for (
            u32 property_index = 0;
            property_index < vertex_property_count;
            ++property_index) {

            // get the property type
            const graphics_vertex_property_type property_type = vertex_property_array[property_index];
            assert(property_type < graphics_vertex_property_type_count);

            // get the method and size for the property
            const vertex_property_method property_method = vertex_property_method_array [property_type];
            const u32                    property_size   = vertex_property_size_array   [property_type];

            // add and enable the property
            property_method(
                renderer->vertex,
                vertex_size,
                property_index,
                offset
            );
            const bool did_enable = gl_vertex_attribute_enable(
                renderer->vertex,
                property_index
            );
            assert(did_enable);

            // update the offset
            offset += property_size;
        }

        // our offset should equal the vertex size at this point
        assert(offset == vertex_size);
    }

    IFB_ENG_INTERNAL void
    graphics_renderer_create_hello_quad(
        graphics_renderer* renderer) {
        
        assert(renderer);

        // initialize pipeline
        gl_pipeline pipeline;
        gl_pipeline_init(pipeline);

        // compile shaders
        constexpr cchar shader_src_vertex[] = 
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        constexpr cchar shader_src_fragment[] =
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "    FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
            "}\0";
        constexpr graphics_vertex_property_type vertex_type[] = {
            graphics_vertex_property_type_vec3
        };
        constexpr u32 vertex_count = 1;
        constexpr u32 vertex_size  = sizeof(vec3);

        graphics_renderer_create(
            renderer,
            shader_src_vertex,
            shader_src_fragment,
            vertex_size,
            vertex_type,
            vertex_count
        );
    }

    IFB_ENG_INTERNAL void
    graphics_renderer_destroy(
        graphics_renderer* renderer) {

        assert(renderer);

        gl_program_destroy (renderer->program);
        gl_buffer_destroy  (renderer->buffer.vertex);
        gl_buffer_destroy  (renderer->buffer.index);
        gl_vertex_destroy  (renderer->vertex);

        memset(
            (void*)renderer,          // dst
            0,                        // val
            sizeof(graphics_renderer) // size
        );
    }

    IFB_ENG_INTERNAL void
    graphics_renderer_draw_buffers(
        graphics_renderer*            renderer,
        const graphics_vertex_buffer& vertex_buffer,
        const graphics_index_buffer&  index_buffer) {

        bool can_render = true;
        can_render &= (renderer != NULL);
        can_render &= (vertex_buffer.is_valid());
        can_render &= (index_buffer.is_valid());
        assert(can_render);

        // update the context
        gl_context_set_program            (renderer->program);
        gl_context_set_vertex             (renderer->vertex);
        gl_context_set_vertex_buffer      (renderer->buffer.vertex);
        gl_context_set_index_buffer       (renderer->buffer.index);
        gl_context_set_vertex_buffer_data (vertex_buffer.data,  vertex_buffer.size);
        gl_context_set_index_buffer_data  (index_buffer.array,  index_buffer.count);

        // draw and reset
        gl_context_render();
        gl_context_reset();
    }
};