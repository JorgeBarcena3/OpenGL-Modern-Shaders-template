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

    shaderProgram.attach(Vertex_Shader(Shader::Source_Code::from_file("../../assets/camera/vertexShader.vglsl")));
    shaderProgram.attach(Fragment_Shader(Shader::Source_Code::from_file("../../assets/camera/fragmentShader.fglsl")));

    shaderProgram.link();
    shaderProgram.use();

    projection_view_matrix_id = shaderProgram.get_uniform_id("camera_matrix");

    updateCameraTransform();


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
    projection_matrix = glm::perspective(glm::radians(40.f), GLfloat(width) / height, 1.f, 100.f);
    glViewport(0, 0, width, height);
}

void OpenGLRender3D::Camera::moveCamera(glm::vec3 direction)
{
    transform.setPosition(transform.getPosition() + (glm::vec3(direction) * cameraTransformAttributes.movement_speed));
}

void OpenGLRender3D::Camera::rotateCamera(sf::Vector2i pos)
{
    
    if (mousePosition.firstPressed)
    {
        mousePosition.lastx = (float)pos.x;
        mousePosition.lasty = (float)pos.y;
        mousePosition.firstPressed = false;
    }

    glm::vec2 offset = glm::vec2({ (float)pos.x - mousePosition.lastx, mousePosition.lasty - (float)pos.y });

    mousePosition.lastx = (float)pos.x;
    mousePosition.lasty = (float)pos.y;


    offset.x *= cameraTransformAttributes.mouse_sensivity;
    offset.y *= cameraTransformAttributes.mouse_sensivity;

    cameraTransformAttributes.yaw   += offset.x;
    cameraTransformAttributes.pitch += offset.y;

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraTransform();

}

const glm::mat4 OpenGLRender3D::Camera::getTransformation()
{
    return glm::lookAt(transform.getPosition(), transform.getPosition() + cameraTransformAttributes.front, cameraTransformAttributes.up);
}

void OpenGLRender3D::Camera::updateCameraTransform()
{

    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(cameraTransformAttributes.yaw)) * cos(glm::radians(cameraTransformAttributes.pitch));
    front.y = sin(glm::radians(cameraTransformAttributes.pitch));
    front.z = sin(glm::radians(cameraTransformAttributes.yaw)) * cos(glm::radians(cameraTransformAttributes.pitch));
    cameraTransformAttributes.front = glm::normalize(front);

    // Also re-calculate the Right and Up vector
    cameraTransformAttributes.right = glm::normalize(glm::cross(cameraTransformAttributes.front, cameraTransformAttributes.worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    cameraTransformAttributes.up = glm::normalize(glm::cross(cameraTransformAttributes.right, cameraTransformAttributes.front));

}
