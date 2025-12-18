#pragma once

#include "graphics.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL bool
    graphics_program_create(
        graphics_program& program) {

        program.pipeline_flags.val = graphics_pipeline_flag_none;

        gl_program_create(
            program.gl_program,
            program.gl_error
        );

        const bool did_create = (
            program.gl_program != GL_PROGRAM_INVALID &&
            program.gl_error   == GL_ERROR_SUCCESS       
        );

        return(did_create);
    }

    IFB_ENG_INTERNAL bool
    graphics_program_destroy(
        graphics_program& program) {

        gl_status destroy_status = GL_ERROR_SUCCESS;
        gl_program_destroy(
            program.gl_program,
            program.gl_error,
            destroy_status
        );

        const bool did_destroy = (
            program.gl_error == GL_ERROR_SUCCESS &&
            destroy_status   == GL_ERROR_SUCCESS            
        );

        return(did_destroy);
    }

    IFB_ENG_INTERNAL bool
    graphics_program_link_pipeline(
        graphics_program&  program,
        graphics_pipeline& pipeline) {

        assert(
            program.gl_program != GL_PROGRAM_INVALID &&
            program.gl_error   == GL_ERROR_SUCCESS
        );

        // attach the compiled shaders in the pipeline to the program
        bool can_link = true;
        for (
            graphics_shader_type shader_type = graphics_shader_type_vertex;
            shader_type < graphics_shader_type_count;
            ++shader_type) {

            // get the shader and make sure it's valid
            graphics_shader& shader = pipeline.shader.array[shader_type];
            const bool should_attach = (
                shader.gl_shader != GL_SHADER_INVALID &&
                shader.gl_error  == GL_ERROR_SUCCESS
            );
            if (!should_attach) continue;

            // attach the shader
            gl_program_attach_shader(
                program.gl_program,
                program.gl_error,
                shader.gl_shader
            );

            // if that worked, set the flag for the shader type
            can_link &= (program.gl_error == GL_ERROR_SUCCESS);
            if (can_link) {
                program.pipeline_flags.set(shader_type);
            }
        }
        if (!can_link) return(can_link);

        // attempt to link the pipeline        
        gl_status link_status = 0;
        gl_program_link(
            program.gl_program,
            program.gl_error,
            link_status
        );
        const bool did_link = (
            program.gl_error == GL_ERROR_SUCCESS &&
            link_status      == GL_TRUE
        );
        return(did_link);
    }
};