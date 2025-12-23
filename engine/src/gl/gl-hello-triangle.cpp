#pragma once

#include "gl.hpp"
#include "sld-vector.hpp"
namespace ifb::eng {

    static unsigned int shaderProgram;
    static unsigned int VBO, VAO, EBO;

    IFB_ENG_INTERNAL void
    gl_hello_triangle_create(
        gl_hello_triangle& hello_triangle) {

        // compile the pipeline
        bool did_compile = true;
        gl_pipeline_init(hello_triangle.pipeline);
        did_compile &= gl_pipeline_compile_shader_vertex   (hello_triangle.pipeline, GL_HELLO_TRIANGLE_SHADER_VERTEX);
        did_compile &= gl_pipeline_compile_shader_fragment (hello_triangle.pipeline, GL_HELLO_TRIANGLE_SHADER_FRAGMENT);

        // create the program and link the pipeline
        gl_program_create(hello_triangle.program);
        const bool did_link = gl_program_link_pipeline(
            hello_triangle.program,
            hello_triangle.pipeline);
        assert(did_link);

        // clean up the pipeline
        gl_pipeline_cleanup(hello_triangle.pipeline);

        // create the buffers and vertex
        gl_buffer_create (hello_triangle.buffer.vertex);
        gl_buffer_create (hello_triangle.buffer.index);
        gl_vertex_create (hello_triangle.vertex);

        // define vertex attributes
        constexpr u32 position_index  = 0;
        constexpr u32 position_offset = 0;
        constexpr u32 vertex_size     = sizeof(vec2); 
        gl_context_set_vertex        (hello_triangle.vertex);
        gl_context_set_vertex_buffer (hello_triangle.buffer.vertex);
        gl_vertex_attribute_set_vec3 (hello_triangle.vertex, vertex_size, position_index, position_offset);
        gl_vertex_attribute_enable   (hello_triangle.vertex, position_index);

        //----------------------
        // LEARNOPENGL
        //----------------------

        // const char *vertexShaderSource = "#version 330 core\n"
        //     "layout (location = 0) in vec3 aPos;\n"
        //     "void main()\n"
        //     "{\n"
        //     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        //     "}\0";
        // const char *fragmentShaderSource = "#version 330 core\n"
        //     "out vec4 FragColor;\n"
        //     "void main()\n"
        //     "{\n"
        //     "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        //     "}\n\0";

        // unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        // glCompileShader(vertexShader);
        // // check for shader compile errors
        // int success;
        // glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        // assert(success);
        // // fragment shader

        // unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        // glCompileShader(fragmentShader);
        // // check for shader compile errors
        // glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        // assert(success);

        // // link shaders
        // shaderProgram = glCreateProgram();
        // glAttachShader(shaderProgram, vertexShader);
        // glAttachShader(shaderProgram, fragmentShader);
        // glLinkProgram(shaderProgram);
        // // check for linking errors
        // glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        // assert(success);

        // // delete shaders
        // glDeleteShader(vertexShader);
        // glDeleteShader(fragmentShader);
            
        // // set up vertex data (and buffer(s)) and configure vertex attributes
        // // ------------------------------------------------------------------
        // float vertices[] = {
        //     0.5f,  0.5f, 0.0f,  // top right
        //     0.5f, -0.5f, 0.0f,  // bottom right
        //     -0.5f, -0.5f, 0.0f,  // bottom left
        //     -0.5f,  0.5f, 0.0f   // top left 
        // };
        // unsigned int indices[] = {  // note that we start from 0!
        //     0, 1, 3,  // first Triangle
        //     1, 2, 3   // second Triangle
        // };
        // glGenVertexArrays(1, &VAO);
        // glGenBuffers(1, &VBO);
        // glGenBuffers(1, &EBO);
        // // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        // glBindVertexArray(VAO);

        // glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        // glEnableVertexAttribArray(0);

        // // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        // glBindBuffer(GL_ARRAY_BUFFER, 0); 

        // // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
        // //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        // glBindVertexArray(0); 
    }

    IFB_ENG_INTERNAL void
    gl_hello_triangle_destroy(
        gl_hello_triangle& hello_triangle) {

        gl_program_destroy(hello_triangle.program);
    }

    IFB_ENG_INTERNAL void
    gl_hello_triangle_render(
        gl_hello_triangle& hello_triangle) {

        const byte* data_buffer_vertex = (byte*)GL_HELLO_TRIANGLE_VERTICES;
        const u32*  data_buffer_index  = (u32*)GL_HELLO_TRIANGLE_INDICES;
        const u32   size_buffer_vertex = sizeof(GL_HELLO_TRIANGLE_VERTICES);
        const u32   size_buffer_index  = sizeof(GL_HELLO_TRIANGLE_INDICES);

        // set the draw data
        gl_context_set_program            (hello_triangle.program);
        gl_context_set_vertex             (hello_triangle.vertex);
        gl_context_set_vertex_buffer      (hello_triangle.buffer.vertex);
        gl_context_set_index_buffer       (hello_triangle.buffer.index);
        gl_context_set_vertex_buffer_data (data_buffer_vertex, size_buffer_vertex);
        gl_context_set_index_buffer_data  (data_buffer_index,  size_buffer_index);
        
        // render data and reset context
        gl_context_render();
        gl_context_reset();

        //----------------------
        // LEARNOPENGL
        //----------------------

        // glUseProgram(shaderProgram);
        // glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // //glDrawArrays(GL_TRIANGLES, 0, 6);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // // glBindVertexArray(0); // no need to unbind it every time 
    }

};