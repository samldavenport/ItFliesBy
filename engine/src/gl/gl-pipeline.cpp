#pragma once

#include "gl.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    gl_pipeline_init(
        gl_pipeline& pipeline) {

        memset(
            (void*)&pipeline,
            0,
            sizeof(gl_pipeline)
        );
    }

    IFB_ENG_INTERNAL void
    gl_pipeline_cleanup(
        gl_pipeline& pipeline) {

        gl_context_clear_errors();

        bool      did_cleanup   = true;
        gl_status delete_status = GL_TRUE;

        if (pipeline.vertex.id != GL_ID_INVALID) {
            glDeleteShader (pipeline.vertex.id);
            glGetShaderiv  (pipeline.vertex.id, GL_DELETE_STATUS, &delete_status);
            did_cleanup &= (delete_status == GL_TRUE);
        }
        if (pipeline.tessellation_control.id != GL_ID_INVALID) {
            glDeleteShader (pipeline.tessellation_control.id);
            glGetShaderiv  (pipeline.tessellation_control.id, GL_DELETE_STATUS, &delete_status);
            did_cleanup &= (delete_status == GL_TRUE);
        }
        if (pipeline.tessellation_evaluation.id != GL_ID_INVALID) {
            glDeleteShader (pipeline.tessellation_evaluation.id);
            glGetShaderiv  (pipeline.tessellation_evaluation.id, GL_DELETE_STATUS, &delete_status);
            did_cleanup &= (delete_status == GL_TRUE);
        }
        if (pipeline.geometry.id != GL_ID_INVALID) {
            glDeleteShader (pipeline.geometry.id);
            glGetShaderiv  (pipeline.geometry.id, GL_DELETE_STATUS, &delete_status);
            did_cleanup &= (delete_status == GL_TRUE);
        }
        if (pipeline.fragment.id != GL_ID_INVALID) {
            glDeleteShader (pipeline.fragment.id);
            glGetShaderiv  (pipeline.fragment.id, GL_DELETE_STATUS, &delete_status);
            did_cleanup &= (delete_status == GL_TRUE);
        }

        assert(did_cleanup);

        memset(
            (void*)&pipeline,
            0,
            sizeof(gl_pipeline)
        );
    }

    IFB_ENG_INTERNAL bool
    gl_pipeline_compile_shader_vertex(
        gl_pipeline& pipeline,
        const cchar* shader_src) {

        // create shader
        pipeline.vertex.id = glCreateShader(GL_VERTEX_SHADER);
        assert(
            shader_src         != NULL &&
            pipeline.vertex.id != GL_ID_INVALID
        );

        // compile shader source
        gl_status compile_status;
        glShaderSource  (pipeline.vertex.id, 1, &shader_src, NULL);
        glCompileShader (pipeline.vertex.id);
        glGetShaderiv   (pipeline.vertex.id, GL_COMPILE_STATUS, &compile_status);

        // check compile status
        const bool did_compile = (compile_status == GL_TRUE);
        pipeline.vertex.error  = (did_compile)
            ? GL_ERROR_SUCCESS
            : glGetError();
        return(did_compile);
    }

    IFB_ENG_INTERNAL bool
    gl_pipeline_compile_shader_tessellation_control(
        gl_pipeline& pipeline,
        const cchar* shader_src) {

        // create shader
        pipeline.tessellation_control.id = glCreateShader(GL_TESS_CONTROL_SHADER);
        assert(
            shader_src                       != NULL &&
            pipeline.tessellation_control.id != GL_ID_INVALID
        );

        // compile shader source
        gl_status compile_status;
        glShaderSource  (pipeline.tessellation_control.id, 1, &shader_src, NULL);
        glCompileShader (pipeline.tessellation_control.id);
        glGetShaderiv   (pipeline.tessellation_control.id, GL_COMPILE_STATUS, &compile_status);

        // check compile status
        const bool did_compile               = (compile_status == GL_TRUE);
        pipeline.tessellation_control.error  = (did_compile)
            ? GL_ERROR_SUCCESS
            : glGetError();
        return(did_compile);
    }

    IFB_ENG_INTERNAL bool
    gl_pipeline_compile_shader_tessellation_evaluation(
        gl_pipeline& pipeline,
        const cchar* shader_src) {

        // create shader
        pipeline.tessellation_evaluation.id = glCreateShader(GL_TESS_EVALUATION_SHADER);
        assert(
            shader_src                       != NULL &&
            pipeline.tessellation_evaluation.id != GL_ID_INVALID
        );

        // compile shader source
        gl_status compile_status;
        glShaderSource  (pipeline.tessellation_evaluation.id, 1, &shader_src, NULL);
        glCompileShader (pipeline.tessellation_evaluation.id);
        glGetShaderiv   (pipeline.tessellation_evaluation.id, GL_COMPILE_STATUS, &compile_status);

        // check compile status
        const bool did_compile                 = (compile_status == GL_TRUE);
        pipeline.tessellation_evaluation.error = (did_compile)
            ? GL_ERROR_SUCCESS
            : glGetError();
        return(did_compile);
    }

    IFB_ENG_INTERNAL bool
    gl_pipeline_compile_shader_geometry(
        gl_pipeline& pipeline,
        const cchar* shader_src) {

        // create shader
        pipeline.geometry.id = glCreateShader(GL_GEOMETRY_SHADER);
        assert(
            shader_src           != NULL &&
            pipeline.geometry.id != GL_ID_INVALID
        );

        // compile shader source
        gl_status compile_status;
        glShaderSource  (pipeline.geometry.id, 1, &shader_src, NULL);
        glCompileShader (pipeline.geometry.id);
        glGetShaderiv   (pipeline.geometry.id, GL_COMPILE_STATUS, &compile_status);

        // check compile status
        const bool did_compile  = (compile_status == GL_TRUE);
        pipeline.geometry.error = (did_compile)
            ? GL_ERROR_SUCCESS
            : glGetError();
        return(did_compile);
    }

    IFB_ENG_INTERNAL bool
    gl_pipeline_compile_shader_fragment(
        gl_pipeline& pipeline,
        const cchar* shader_src) {

        // create shader
        pipeline.fragment.id = glCreateShader(GL_FRAGMENT_SHADER);
        assert(
            shader_src           != NULL &&
            pipeline.fragment.id != GL_ID_INVALID
        );

        // compile shader source
        gl_status compile_status;
        glShaderSource  (pipeline.fragment.id, 1, &shader_src, NULL);
        glCompileShader (pipeline.fragment.id);
        glGetShaderiv   (pipeline.fragment.id, GL_COMPILE_STATUS, &compile_status);

        // check compile status
        const bool did_compile  = (compile_status == GL_TRUE);
        pipeline.fragment.error = (did_compile)
            ? GL_ERROR_SUCCESS
            : glGetError();
        return(did_compile);
    }
};