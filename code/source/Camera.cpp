#include "..\header\Camera.hpp"
#include "../header/Vertex_Shader.hpp"
#include "../header/Fragment_Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr
#include <algorithm>

OpenGLRender3D::Camera::Camera(int width, int height, Scene& _scene)
{

    scene = &_scene;

    resize(width, height);

    // Se compilan y se activan los shaders:

    shaderProgram.attach(Vertex_Shader(Shader::Source_Code::from_file("../../assets/vertexShader.vglsl")));
    shaderProgram.attach(Fragment_Shader(Shader::Source_Code::from_file("../../assets/fragmentShader.fglsl")));

    shaderProgram.link();

    projection_view_matrix_id = shaderProgram.get_uniform_id("projection_view_matrix");

}

void OpenGLRender3D::Camera::update(float time)
{

    static float angle = 0;

    angle = 1.0f;

    transform.getModelViewMatrix();

}

void OpenGLRender3D::Camera::render()
{

    shaderProgram.use();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

}

void OpenGLRender3D::Camera::resize(int width, int height)
{
    scene->setWindowSize(width, height);
    projection_matrix = glm::perspective(40.f, GLfloat(width) / height, 1.f, 100.f);
    glViewport(0, 0, width, height);
}

void OpenGLRender3D::Camera::moveCamera(glm::vec3 direction)
{
    transform.setPosition(transform.getPosition() + (glm::vec3(direction)   ));
}

void OpenGLRender3D::Camera::rotateCamera(glm::vec2 mousePos)
{

    float dead_zone = 100;
    float speed_rot = 20;

    // X rotation
    float center_x = (scene->getWindowSize().x) / 2;
    float distanceToCenter = (mousePos.x - (center_x));

    float rotation = distanceToCenter > dead_zone ? -speed_rot : distanceToCenter < -dead_zone ? +speed_rot : 0;

    if (rotation != 0)
    {

        transform.setRotation(transform.getRotation() + (transform.getUpVector() * glm::vec3(0, rotation, 0)));


    }
    else
    {
        float center_y = (scene->getWindowSize().y) / 2;
        distanceToCenter = (mousePos.y - (center_y));

        rotation = distanceToCenter > dead_zone ? -speed_rot : distanceToCenter < -dead_zone ? speed_rot : 0;
        transform.setRotation(transform.getRotation() + (transform.getRightVector() * glm::vec3(rotation, rotation, rotation)));
    }

}
