
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on may of 2014                                            *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <glm\gtc\type_ptr.hpp>

#include "../../header/Vertex_Shader.hpp"
#include "../../header/Fragment_Shader.hpp"
#include "../../header/exampleShapes/Skybox.hpp"
#include "../../header/Cubemap.hpp"
#include "../../header/Camera.hpp"

namespace OpenGLRender3D
{

    GLfloat coordinates[] =
    {
        -1.0f, +1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        +1.0f, -1.0f, -1.0f,
        +1.0f, -1.0f, -1.0f,
        +1.0f, +1.0f, -1.0f,
        -1.0f, +1.0f, -1.0f,
        -1.0f, -1.0f, +1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, +1.0f, -1.0f,
        -1.0f, +1.0f, -1.0f,
        -1.0f, +1.0f, +1.0f,
        -1.0f, -1.0f, +1.0f,
        +1.0f, -1.0f, -1.0f,
        +1.0f, -1.0f, +1.0f,
        +1.0f, +1.0f, +1.0f,
        +1.0f, +1.0f, +1.0f,
        +1.0f, +1.0f, -1.0f,
        +1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, +1.0f,
        -1.0f, +1.0f, +1.0f,
        +1.0f, +1.0f, +1.0f,
        +1.0f, +1.0f, +1.0f,
        +1.0f, -1.0f, +1.0f,
        -1.0f, -1.0f, +1.0f,
        -1.0f, +1.0f, -1.0f,
        +1.0f, +1.0f, -1.0f,
        +1.0f, +1.0f, +1.0f,
        +1.0f, +1.0f, +1.0f,
        -1.0f, +1.0f, +1.0f,
        -1.0f, +1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, +1.0f,
        +1.0f, -1.0f, -1.0f,
        +1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, +1.0f,
        +1.0f, -1.0f, +1.0f,
    };

    Skybox::Skybox(const std::string& path, Scene& _scene, OpenGLRender3D::OPACITYMODEL op) : BaseModel3D(op, _scene)
    {
        textures_factory.push_back( new Cubemap(path) );


        shaderProgram.attach(ShaderProgramHelper::Vertex_Shader(ShaderProgramHelper::Shader::Source_Code::from_file("../../assets/skybox/vertexShader.vglsl")));
        shaderProgram.attach(ShaderProgramHelper::Fragment_Shader(ShaderProgramHelper::Shader::Source_Code::from_file("../../assets/skybox/fragmentShader.fglsl")));

        shaderProgram.link();

        // Se generan índices para los VBOs del cubo:

        glGenBuffers(VBO_COUNT, vbo_ids);
        glGenVertexArrays(1, &vao_id);

        // Se activa el VAO del cubo para configurarlo:

        glBindVertexArray(vao_id);

        // Se suben a un VBO los datos de coordenadas y se vinculan al VAO:

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates), coordinates, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        transform.setScale(glm::vec3(5, 5, 5));
    }

    Skybox::~Skybox()
    {
        // Se liberan los VBOs y el VAO usados:

        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers(VBO_COUNT, vbo_ids);
    }


    void Skybox::update(float time)
    {
        transform.setPosition(scene->getMainCamera()->transform.getPosition() + (glm::vec3(0, 0, -2.5f)));
    }

    void Skybox::render()
    {

        glDepthMask(GL_FALSE);
        shaderProgram.use();
        
        textures_factory[0]->bind();

        glm::mat4 projection_view_matrix = scene->getMainCamera()->getProjectionMatrix() * scene->getMainCamera()->getTransformation() * transform.getModelViewMatrix();
        //glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix));
        glUniformMatrix4fv(scene->getMainCamera()->getProjectionMatrixId(), 1, GL_FALSE, glm::value_ptr(projection_view_matrix));


        glBindVertexArray(vao_id);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glDepthMask(GL_TRUE);

        shaderProgram.disable();

    }

}
