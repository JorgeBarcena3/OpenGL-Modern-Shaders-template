#include "..\header\Camera.hpp"
#include "../header/Vertex_Shader.hpp"
#include "../header/Fragment_Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr
#include <algorithm>

OpenGLRender3D::Camera::Camera(int width, int height, Scene& _scene)
{
    resize(width, height);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    scene = &_scene;
    // Se compilan y se activan los shaders:

    shaderProgram.attach(Vertex_Shader(Shader::Source_Code::from_file("../../assets/vertexShader.vglsl")));
    shaderProgram.attach(Fragment_Shader(Shader::Source_Code::from_file("../../assets/fragmentShader.fglsl")));

    shaderProgram.link();

    projection_matrix = glm::perspective(20.f, GLfloat(width) / height, 1.f, 50.f);
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
    glEnable(GL_DEPTH_TEST);


}


void OpenGLRender3D::Camera::resize(int width, int height)
{
    // Se establece la configuración básica:
    projection_matrix = glm::perspective(glm::radians(20.f), GLfloat(width) / height, 1.f, 100.f);
    glViewport(0, 0, width, height);
}

void OpenGLRender3D::Camera::moveCamera(glm::vec3 direction)
{
    transform.setPosition(transform.getPosition() + ( glm::vec3(direction)  * 0.2f));
}

void OpenGLRender3D::Camera::rotateCamera(glm::vec2 mousePos)
{

    float dead_zone = 100;
    float speed_rot = 5;

    // X rotation
    float center_x = ( scene->getWindowSize().x )  / 2;
    float distanceToCenter =  (mousePos.x - (center_x) );

    float rotation = distanceToCenter > dead_zone ? -speed_rot : distanceToCenter < -dead_zone ? +speed_rot : 0;
    transform.setRotation(transform.getRotation() + glm::vec3(0, rotation, 0));
    
    float center_y = ( scene->getWindowSize().y )  / 2;
    distanceToCenter =  (mousePos.y - (center_y) );

    rotation = distanceToCenter > dead_zone ? -speed_rot : distanceToCenter < -dead_zone ? speed_rot : 0;
    transform.setRotation(transform.getRotation() + glm::vec3(rotation,0 , 0));



}
