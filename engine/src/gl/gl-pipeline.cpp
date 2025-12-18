#pragma once

#include "gl.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    gl_pipeline_init(
        gl_pipeline& pipeline) {

        pipeline.vertex                  = GL_SHADER_INVALID; 
        pipeline.tessellation_control    = GL_SHADER_INVALID; 
        pipeline.tessellation_evaluation = GL_SHADER_INVALID; 
        pipeline.geometry                = GL_SHADER_INVALID; 
        pipeline.fragment                = GL_SHADER_INVALID; 
    }

    IFB_ENG_INTERNAL bool
    gl_pipeline_cleanup(
        gl_pipeline& pipeline) {

        gl_context_clear_errors();

        bool      did_cleanup   = true;
        gl_status delete_status = GL_TRUE;

        if (pipeline.vertex != GL_SHADER_INVALID) {
            glDeleteShader (pipeline.vertex);
            glGetShaderiv  (pipeline.vertex, GL_DELETE_STATUS, &delete_status);
            did_cleanup &= (status == GL_TRUE);
        }
        if (pipeline.tessellation_control != GL_SHADER_INVALID) {
            glDeleteShader (pipeline.tessellation_control);
            glGetShaderiv  (pipeline.tessellation_control, GL_DELETE_STATUS, &delete_status);
            did_cleanup &= (status == GL_TRUE);
        }
        if (pipeline.tessellation_evaluation != GL_SHADER_INVALID) {
            glDeleteShader (pipeline.tessellation_evaluation);
            glGetShaderiv  (pipeline.tessellation_evaluation, GL_DELETE_STATUS, &delete_status);
            did_cleanup &= (status == GL_TRUE);
        }
        if (pipeline.geometry != GL_SHADER_INVALID) {
            glDeleteShader (pipeline.geometry);
            glGetShaderiv  (pipeline.geometry, GL_DELETE_STATUS, &delete_status);
            did_cleanup &= (status == GL_TRUE);
        }
        if (pipeline.fragment != GL_SHADER_INVALID) {
            glDeleteShader (pipeline.fragment);
            glGetShaderiv  (pipeline.fragment, GL_DELETE_STATUS, &delete_status);
            did_cleanup &= (status == GL_TRUE);
        }

        return(did_cleanup);
    }

    IFB_ENG_INTERNAL bool
    gl_pipeline_compile_shader_vertex(
        gl_pipeline& pipeline,
        const cchar* shader_src) {

        shader = glCreateShader (GL_VERTEX_SHADER);
        error  = (shader == GL_SHADER_INVALID) ? glGetError() : GL_ERROR_SUCCESS;

    }

    IFB_ENG_INTERNAL bool
    gl_pipeline_compile_shader_tessellation_control(
        gl_pipeline& pipeline,
        const cchar* shader_src) {

    }

    IFB_ENG_INTERNAL bool
    gl_pipeline_compile_shader_tessellation_evaluation(
        gl_pipeline& pipeline,
        const cchar* shader_src) {

    }

    IFB_ENG_INTERNAL bool
    gl_pipeline_compile_shader_geometry(
        gl_pipeline& pipeline,
        const cchar* shader_src) {

    }

    IFB_ENG_INTERNAL bool
    gl_pipeline_compile_shader_fragment(
        gl_pipeline& pipeline,
        const cchar* shader_src) {

    }
};