#pragma once

#include "gl.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL void
    gl_program_create(
        gl_program& program) {

        program.id    = glCreateProgram();
        program.error = GL_ERROR_SUCCESS;
        assert(program.id != GL_ID_INVALID); 
    }

    IFB_ENG_INTERNAL void
    gl_program_destroy(
        gl_program& program) {

        glDeleteProgram(program.id);

        gl_status delete_status;
        glGetProgramiv(program.id, GL_DELETE_STATUS, &delete_status);
        const bool did_delete = (delete_status == GL_TRUE);
        assert(did_delete);

        program.error = GL_ERROR_SUCCESS;
        program.id    = GL_ID_INVALID; 
    }

    IFB_ENG_INTERNAL bool
    gl_program_link_pipeline(
        gl_program&  program,
        gl_pipeline& pipeline) {

        // clear errors and check args
        gl_context_clear_errors();
        assert(
            program.id    != GL_ID_INVALID &&
            program.error == GL_ERROR_SUCCESS
        );

        // determine shaders to attach
        const bool attach_shader_vertex    = (pipeline.vertex.id                  != GL_ID_INVALID);
        const bool attach_shader_tess_ctrl = (pipeline.tessellation_control.id    != GL_ID_INVALID);
        const bool attach_shader_tess_eval = (pipeline.tessellation_evaluation.id != GL_ID_INVALID);
        const bool attach_shader_geometry  = (pipeline.geometry.id                != GL_ID_INVALID);
        const bool attach_shader_fragment  = (pipeline.fragment.id                != GL_ID_INVALID);

        // attach shaders
        bool can_link = true;
        if (attach_shader_vertex) {
            glAttachShader(program.id, pipeline.vertex.id);
            can_link &= (glGetError() == GL_ERROR_SUCCESS); 
            can_link &= (pipeline.vertex.error == GL_ERROR_SUCCESS); 
        }
        if (attach_shader_tess_ctrl) {
            glAttachShader(program.id, pipeline.tessellation_control.id);
            can_link &= (glGetError() == GL_ERROR_SUCCESS); 
            can_link &= (pipeline.tessellation_control.error == GL_ERROR_SUCCESS);
        }
        if (attach_shader_tess_eval) {
            glAttachShader(program.id, pipeline.tessellation_evaluation.id);
            can_link &= (glGetError() == GL_ERROR_SUCCESS); 
            can_link &= (pipeline.tessellation_evaluation.error == GL_ERROR_SUCCESS);
        }
        if (attach_shader_geometry) {
            glAttachShader(program.id, pipeline.geometry.id);
            can_link &= (glGetError() == GL_ERROR_SUCCESS); 
            can_link &= (pipeline.geometry.error == GL_ERROR_SUCCESS);
        }
        if (attach_shader_fragment) {
            glAttachShader(program.id, pipeline.fragment.id);
            can_link &= (glGetError() == GL_ERROR_SUCCESS); 
            can_link &= (pipeline.fragment.error == GL_ERROR_SUCCESS);
        }
        assert(can_link);

        // link program
        gl_status link_status;
        glLinkProgram  (program.id);
        glGetProgramiv (program.id, GL_LINK_STATUS, &link_status);
        
        // check link status
        const bool did_link = (link_status == GL_TRUE);
        program.error = (did_link) ? GL_ERROR_SUCCESS : glGetError();
        return(did_link);
    }

    IFB_ENG_INTERNAL void
    gl_program_set_active(
        gl_program& program) {

        gl_context_clear_errors();

        glUseProgram(program.id);
    
        const gl_error error = glGetError();
        assert(error == GL_ERROR_SUCCESS);
    }
};