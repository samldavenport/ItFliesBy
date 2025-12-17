#pragma once

#include "graphics.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    graphics_pipeline_init(
        graphics_pipeline& pipeline) {
        
        pipeline.shader.vertex.gl_shader                  = GL_SHADER_INVALID;
        pipeline.shader.vertex.gl_error                   = GL_ERROR_SUCCESS;

        pipeline.shader.tessellation_control.gl_shader    = GL_SHADER_INVALID;
        pipeline.shader.tessellation_control.gl_error     = GL_ERROR_SUCCESS;
        
        pipeline.shader.tessellation_evaluation.gl_shader = GL_SHADER_INVALID;
        pipeline.shader.tessellation_evaluation.gl_error  = GL_ERROR_SUCCESS;
        
        pipeline.shader.geometry.gl_shader                = GL_SHADER_INVALID;
        pipeline.shader.geometry.gl_error                 = GL_ERROR_SUCCESS;
        
        pipeline.shader.fragment.gl_shader                = GL_SHADER_INVALID;
        pipeline.shader.fragment.gl_error                 = GL_ERROR_SUCCESS;
        
    }

    IFB_ENG_INTERNAL bool
    graphics_pipeline_cleanup(
        graphics_pipeline& pipeline) {
    
        bool did_cleanup = true;

        for (
            graphics_shader_type shader_type = graphics_shader_type_vertex;
            shader_type < graphics_shader_type_count;
            ++shader_type) {

            graphics_shader& shader = pipeline.shader.array[shader_type];
            if (shader.gl_shader != GL_SHADER_INVALID) {

                gl_shader_destroy(shader.gl_shader, shader.gl_error);                
                did_cleanup &= (shader.gl_error == GL_ERROR_SUCCESS);
            }
        }

        return(did_cleanup);
    }

    IFB_ENG_INTERNAL void
    graphics_pipeline_clear_errors(
        graphics_pipeline& pipeline) {

        pipeline.shader.vertex.gl_error                  = GL_ERROR_SUCCESS;
        pipeline.shader.tessellation_control.gl_error    = GL_ERROR_SUCCESS;
        pipeline.shader.tessellation_evaluation.gl_error = GL_ERROR_SUCCESS;
        pipeline.shader.geometry.gl_error                = GL_ERROR_SUCCESS;
        pipeline.shader.fragment.gl_error                = GL_ERROR_SUCCESS;
    }

    IFB_ENG_INTERNAL bool
    graphics_pipeline_compile_shader_vertex(
        graphics_pipeline& pipeline,
        const cchar*       shader_src) {

        assert(shader_src);

        gl_status        shader_status = GL_ERROR_SUCCESS;
        graphics_shader& shader        = pipeline.shader.vertex;

        // create the shader
        gl_shader_create_vertex(
            shader.gl_shader,
            shader.gl_error
        );
        const bool did_create = (
            shader.gl_shader != GL_SHADER_INVALID &&
            shader.gl_error  == GL_ERROR_SUCCESS
        );
        if (!did_create) return(did_create);

        // compile the shader source
        gl_shader_compile(
            shader.gl_shader,
            shader.gl_error,
            shader_status,
            shader_src
        );
        const bool did_compile = (
            shader.gl_shader != GL_SHADER_INVALID &&
            shader.gl_error  == GL_ERROR_SUCCESS        
        );
        return(did_compile);
    }

    IFB_ENG_INTERNAL bool
    graphics_pipeline_compile_shader_tessellation_control(
        graphics_pipeline& pipeline,
        const cchar*       shader_src) {

        assert(shader_src);
    }

    IFB_ENG_INTERNAL bool
    graphics_pipeline_compile_shader_tessellation_evaluation(
        graphics_pipeline& pipeline,
        const cchar*       shader_src) {

        assert(shader_src);
    }

    IFB_ENG_INTERNAL bool
    graphics_pipeline_compile_shader_geometry(
        graphics_pipeline& pipeline,
        const cchar*       shader_src) {

        assert(shader_src);
    }

    IFB_ENG_INTERNAL bool
    graphics_pipeline_compile_shader_fragment(
        graphics_pipeline& pipeline,
        const cchar*       shader_src) {

        assert(shader_src);
    }
};