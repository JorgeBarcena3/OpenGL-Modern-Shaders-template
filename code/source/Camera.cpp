#include "..\header\Camera.hpp"
#include "../header/Vertex_Shader.hpp"
#include "../header/Fragment_Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

OpenGLRender3D::Camera::Camera(int width, int height)
{
    resize(width, height);
    //glEnable     (GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // Se compilan y se activan los shaders:

    shaderProgram.attach(Vertex_Shader(Shader::Source_Code::from_file("../../assets/vertexShader.vglsl")));
    shaderProgram.attach(Fragment_Shader(Shader::Source_Code::from_file("../../assets/fragmentShader.fglsl")));

    shaderProgram.link();
    shaderProgram.use();

    projection_matrix = glm::perspective(20.f, GLfloat(width) / height, 1.f, 50.f);
    projection_view_matrix_id = shaderProgram.get_uniform_id("projection_view_matrix");

}

void OpenGLRender3D::Camera::update(float time)
{
    transform.setRotation( glm::vec3(0, 0, -0.1));
}

void OpenGLRender3D::Camera::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
}


void OpenGLRender3D::Camera::resize(int width, int height)
{
    // Se establece la configuración básica:
    projection_matrix = glm::perspective(20.f, GLfloat(width) / height, 1.f, 50.f);
    glViewport(0, 0, width, height);
}

bool OpenGLRender3D::Camera::uploadUniformVariable(const char* name, float value)
{
    GLint id = shaderProgram.get_uniform_id(name);

    if (id != -1)
    {
        shaderProgram.set_uniform_value(id, value);
        return true;

    }

    return false;
}

bool OpenGLRender3D::Camera::uploadUniformVariable(const char* name, Vector3f value)
{
    GLint id = shaderProgram.get_uniform_id(name);

    if (id != -1)
    {
        shaderProgram.set_uniform_value(id, value);
        return true;
    }

    return false;
}
