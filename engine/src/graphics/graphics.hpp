#ifndef IFB_ENGINE_GRAPHICS_HPP
#define IFB_ENGINE_GRAPHICS_HPP

#include "ifb-engine.hpp"
#include "gl.hpp"

using namespace sld;

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct graphics_manager;
    struct graphics_pipeline;

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

    graphics_manager* graphics_manager_alloc              (stack& stack);
    void              graphics_manager_startup            (graphics_manager* graphics);
    void              graphics_manager_shutdown           (graphics_manager* graphics);
    void              graphics_pipeline_create_hello_quad (graphics_manager* graphics);

    //-------------------------------------------------------------------
    // ENUMS
    //-------------------------------------------------------------------

    

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct graphics_manager {
        graphics_pipeline* hello_quad_pipeline;
    };

    struct graphics_pipeline {
        gl_program program;
        gl_vertex  vertex;
        struct {
            gl_buffer vertex;
            gl_buffer index;
        } buffer;
    };
};

#endif //IFB_ENGINE_GRAPHICS_HPP