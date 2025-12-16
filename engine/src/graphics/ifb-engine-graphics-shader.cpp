#pragma once

#include "ifb-engine-graphics-shader.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL bool
    shader_create(
        shader*                  shdr,
        const shader_stage_flags stage_flags) {

        // initialize
        assert(shdr != NULL);
        shdr->program.gl_program      = GL_ERROR_SUCCESS; 
        shdr->program.gl_error        = GL_PROGRAM_INVALID; 
        shdr->stage.flags             = pipeline_stage_flag_e_none;
        shdr->stage.vertex.gl_stage   = GL_SHADER_STAGE_INVALID;
        shdr->stage.vertex.gl_error   = GL_ERROR_SUCCESS;
        shdr->stage.fragment.gl_stage = GL_SHADER_STAGE_INVALID;
        shdr->stage.fragment.gl_error = GL_ERROR_SUCCESS;

        // create gl program
        gl_program_create(shdr->program.gl_program, shdr->program.gl_error);
        bool did_create = (
            shdr->program.gl_program != GL_PROGRAM_INVALID &&
            shdr->program.gl_error   == GL_ERROR_SUCCESS
        );
        if (!did_create) return(did_create);

        // shader create method array corresponds with shader types
        using func_gl_shader_create = void (*) (gl_shader& stage, gl_error& error);
        constexpr func_gl_shader_create stage_create_method_array[] = {
            gl_shader_create_vertex,
            gl_shader_create_fragment
        };
        for (
            shader_stage_type stage_type = shader_type_vertex;
            stage_type < shader_type_count;
            ++stage_type) {

            // check if we should create this stage
            const u32  flag_val      = (1 << stage_type); 
            const bool should_create = shdr->stage.flags.test(flag_val);
            if (!should_create) continue;

            // get the stage and corresponding create method
            const func_gl_shader_create create_method = stage_create_method_array [stage_type];
            shader_stage&               stage         = shdr->stage.array         [stage_type]; 

            // create the stage
            create_method(stage.gl_stage, stage.gl_error);
            const bool stage_is_created = (
                stage.gl_stage != GL_SHADER_STAGE_INVALID &&
                stage.gl_error == GL_ERROR_SUCCESS
            );

            // update shader
            if (stage_is_created) shdr->stage.flags.set(stage_type);
            did_create &= stage_is_created;
        }

        // done
        return(did_create);
    }

    IFB_ENG_INTERNAL bool
    shader_add_stage_source_from_file(
        shader*                 shdr,
        const shader_stage_type type,
        const cchar*            file_path) {

        // check args
        bool can_add = true;
        can_add &= (shdr != NULL);                    
        can_add &= (type <  shader_type_count); 
        can_add &= (src_buffer != NULL);
        if (can_add) {
            can_add &= (shdr->program.gl_program != GL_PROGRAM_INVALID);
            can_add &= (shdr->program.gl_error   != GL_ERROR_SUCCESS);
            can_add &= shdr->stage.flags.test(type);
        }
        assert(can_add);

        // TODO(SLD): implement

        panic();
    }


    IFB_ENG_INTERNAL bool
    shader_add_stage_source_from_buffer(
        shader*                 shdr,
        const shader_stage_type type,
        const cchar*            src_buffer) {

        // check args
        bool can_add = true;
        can_add &= (shdr != NULL);                    
        can_add &= (type <  shader_type_count); 
        can_add &= (src_buffer != NULL);
        if (can_add) {
            can_add &= (shdr->program.gl_program != GL_PROGRAM_INVALID);
            can_add &= (shdr->program.gl_error   != GL_ERROR_SUCCESS);
            can_add &= shdr->stage.flags.test(type);
        }
        assert(can_add);

        // compile the stage
        shader_stage& stage = shdr->stage.array[type];
        gl_status compile_status = 0;
        gl_shader_compile(
            stage.gl_stage,
            stage.gl_error,
            compile_status,
            src_buffer
        );

        // check compile status
        const bool did_compile = (
            stage.gl_stage != GL_SHADER_STAGE_INVALID &&
            stage.gl_error == GL_ERROR_SUCCESS &&
            compile_status == GL_ERROR_SUCCESS
        );
        return(did_compile);
    }

    IFB_ENG_INTERNAL bool
    shader_link_stages(
        shader* shdr) {

        assert(shdr);

        gl_status link_status = 0;
        gl_program_link(
            shdr->program.gl_program,
            shdr->program.gl_error,
            link_status
        );

        const bool did_link = (
            shdr->program.gl_error == GL_ERROR_SUCCESS &&
            link_status            == GL_ERROR_SUCCESS
        );
        return(did_link);
    }

    IFB_ENG_INTERNAL void
    shader_reset(
        shader* shdr) {

        assert(shdr);
        shdr->program.gl_error        = GL_ERROR_SUCCESS;
        shdr->stage.vertex.gl_error   = GL_ERROR_SUCCESS;
        shdr->stage.fragment.gl_error = GL_ERROR_SUCCESS;
    }

    IFB_ENG_INTERNAL bool
    shader_destroy(
        shader* shdr) {
    
        assert(shdr);

        shdr->program.gl_error        = GL_ERROR_SUCCESS;
        shdr->stage.vertex.gl_error   = GL_ERROR_SUCCESS;
        shdr->stage.fragment.gl_error = GL_ERROR_SUCCESS;

        gl_shader_destroy(
            
        )

    
    }
};