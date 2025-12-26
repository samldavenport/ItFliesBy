#ifndef IFB_ENGINE_GRAPHICS_HPP
#define IFB_ENGINE_GRAPHICS_HPP

#include "ifb-engine.hpp"
#include "gl.hpp"
#include "math.hpp"

using namespace sld;

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using graphics_vertex_property_type = u32;
    
    struct graphics_manager;
    struct graphics_renderer;
    struct graphics_vertex_buffer;
    struct graphics_index_buffer;

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr f32 GRAPHICS_QUAD_VERTEX_DATA[] = {
         0.5f,  0.5f, 0.0f, // top right
         0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f  // top left 
    };

    constexpr u32 GRAPHICS_QUAD_INDEX_DATA[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    // manager
    IFB_ENG_INTERNAL graphics_manager* graphics_manager_alloc              (stack& stack);
    IFB_ENG_INTERNAL void              graphics_manager_startup            (graphics_manager* graphics);
    IFB_ENG_INTERNAL void              graphics_manager_shutdown           (graphics_manager* graphics);
    IFB_ENG_INTERNAL void              graphics_manager_render_hello_quad  (graphics_manager* graphics);

    // renderer
    IFB_ENG_INTERNAL void
    graphics_renderer_create(
        graphics_renderer*                   renderer,
        const cchar*                         shader_src_vertex,
        const cchar*                         shader_src_fragment,
        const u32                            vertex_size,
        const graphics_vertex_property_type* vertex_property_array,
        const u32                            vertex_property_count
    );
    IFB_ENG_INTERNAL void graphics_renderer_set_active        (graphics_renderer* renderer);
    IFB_ENG_INTERNAL void graphics_renderer_create_hello_quad (graphics_renderer* renderer);
    IFB_ENG_INTERNAL void graphics_renderer_destroy           (graphics_renderer* renderer);

    IFB_ENG_INTERNAL void
    graphics_renderer_draw_buffers(
        graphics_renderer*            renderer,
        const graphics_vertex_buffer& vertex_buffer,
        const graphics_index_buffer&  index_buffer);

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    enum graphics_vertex_property_type_ {
        graphics_vertex_property_type_s32   = 0,
        graphics_vertex_property_type_u32   = 1,
        graphics_vertex_property_type_f32   = 2,
        graphics_vertex_property_type_vec2  = 3,
        graphics_vertex_property_type_vec3  = 4,
        graphics_vertex_property_type_count = 5
    };

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct graphics_manager {
        graphics_renderer* hello_quad_renderer;
    };

    struct graphics_renderer {
        gl_program program;
        gl_vertex  vertex;
        struct {
            gl_buffer vertex;
            gl_buffer index;
        } buffer;
    };

    struct graphics_vertex_buffer {
        byte* data;
        u32   size;

        inline bool
        is_valid(void) const {
            return(
                (size != 0)    &&
                (data != NULL)
            );
        }
    };
    
    struct graphics_index_buffer {
        u32* array;
        u32  count;

        inline bool
        is_valid(void) const {
            return(
                (count != 0) &&
                (array != NULL)
            );
        }
    };
};

#endif //IFB_ENGINE_GRAPHICS_HPP