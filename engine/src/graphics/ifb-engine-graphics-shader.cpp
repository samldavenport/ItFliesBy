#pragma once

#include "ifb-engine-graphics-shader.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL bool
    shader_create(
        shader* shdr) {

        // initialize
        assert(shdr != NULL);
        shdr->program.gl_program      = GL_ERROR_SUCCESS; 
        shdr->program.gl_error        = GL_SHADER_PROGRAM_INVALID; 
        shdr->stage.flags             = shader_stage_flag_e_none;
        shdr->stage.vertex.gl_stage   = GL_SHADER_STAGE_INVALID;
        shdr->stage.vertex.gl_error   = GL_ERROR_SUCCESS;
        shdr->stage.fragment.gl_stage = GL_SHADER_STAGE_INVALID;
        shdr->stage.fragment.gl_error = GL_ERROR_SUCCESS;

        // create gl program
        gl_shader_program_create(
            shdr->program.gl_program,
            shdr->program.gl_error
        );

        // check program
        const bool did_create = (
            shdr->program.gl_program != GL_SHADER_PROGRAM_INVALID &&
            shdr->program.gl_error   == GL_ERROR_SUCCESS
        );
        return(did_create);
    }

    IFB_ENG_INTERNAL bool
    shader_add_stage_from_file(
        shader*                 shdr,
        const shader_stage_type type,
        const cchar*            file_path) {

        // TODO

        panic();
    }

    using func_gl_shader_create = void (*) (gl_shader_stage& stage, gl_error& error);

    IFB_ENG_INTERNAL bool
    shader_add_stage_from_source(
        shader*                 shdr,
        const shader_stage_type type,
        const cchar*            src_buffer) {

        // check args
        bool can_create = (shdr != NULL);
        if (can_create) {
            can_create &= (shdr       != NULL);
            can_create &= (src_buffer != NULL);
            can_create &= (type < shader_stage_type_e_count);
            can_create &= (shdr->program.gl_error != GL_SHADER_PROGRAM_INVALID);
            can_create &= (shdr->program.gl_error == GL_ERROR_SUCCESS);
        }
        assert(can_create);

        // shader create method array corresponds with shader types
        constexpr func_gl_shader_create stage_create_method_array[] = {
            gl_shader_stage_create_vertex,
            gl_shader_stage_create_fragment
        };

        // get the shader stage and create method
        func_gl_shader_create& stage_create_method = stage_create_method_array [type]; 
        shader_stage&          stage               = shdr->stage.array         [type];

        // create the stage
        stage_create_method(
            stage.gl_stage,
            stage.gl_error);

        // if we created the stage, toggle the corresponding flag
        const bool did_create = (
            shdr->stage.fragment.stage != GL_SHADER_STAGE_INVALID &&
            shdr->stage.fragment.error == GL_ERROR_SUCCESS
        );
        shdr->stage.flags |= did_create ? bit_value(type) : shader_stage_flag_e_none;

        // done
        return(did_create);
    }

    IFB_ENG_INTERNAL bool
    shader_compile_and_link(
        shader* shdr) {

        bool can_compile = (shdr != NULL);
        if (can_compile) {
            can_compile &= (shdr->program.gl_program != GL_SHADER_PROGRAM_INVALID);
            can_compile &= (shdr->program.gl_error   == GL_ERROR_SUCCESS);
        }
        assert(can_compile);

        bool      did_compile    = true;
        gl_status compile_status = 0;
        for (
            u32 shader_type = 0;
            shader_type < shader_stage_type_e_count;
            ++shader_type) {

            // check if we should try to compile this stage
            // if not, skip
            const bool should_compile = (shdr->stage.flags & bit_value(shader_type));
            if (!should_compile) continue;
                
            // get the stage and attempt to compile
            shader_stage& stage = shdr->stage.array[shader_type];
            gl_shader_stage_compile(
                stage.gl_stage,
                stage.gl_error
            );

            // check if the stage is compiled
            did_compile &= stage.gl_stage != GL_SHADER_STAGE_INVALID;
            did_compile &= stage.gl_error == GL_ERROR_SUCCESS; 
        }


    }

    IFB_ENG_INTERNAL bool
    shader_destroy(
        shader* shdr) {
    
    }
};