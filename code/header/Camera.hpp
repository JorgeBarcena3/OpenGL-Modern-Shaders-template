
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define GLM_FORCE_RADIANS

#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <string>
#include <glm/matrix.hpp>

#include "Shader_Program.hpp"
#include "3DModels/BaseModel3D.hpp"


namespace OpenGLRender3D
{

    using namespace ShaderProgramHelper;

    class Camera
    {

        struct MousePosition
        {
            float lastx;
            float lasty;
            bool firstPressed = true;
        };

        struct CameraTransformAttributes
        {
            // Camera Attributes
            glm::vec3 front;
            glm::vec3 up;
            glm::vec3 right;
            glm::vec3 worldUp;

            // Euler Angles
            float yaw;
            float pitch;

            // Camera options
            float movement_speed;
            float mouse_sensivity;

            CameraTransformAttributes()
            {
                worldUp = glm::vec3(0.f, 1., 0.f);
                yaw = -90.f;
                pitch = 0;
                movement_speed     = 0.15f;
                mouse_sensivity  = 0.2f;
            }
        };

    public:

        Transform transform;

        CameraTransformAttributes cameraTransformAttributes;

        MousePosition mousePosition;

    private:

        GLint  projection_view_matrix_id;
        GLint  cameraposition_id;

        glm::mat4 projection_matrix;

        Shader_Program shaderProgram;

        Scene* scene;

    public:

        Camera(int width, int height, Scene& scene);

        void   update(float time);
        void   render();
        void   resize(int width, int height);

        void moveCamera(glm::vec3 movement);
        void rotateCamera(glm::vec2 mousePos);

        const GLint getProjectionMatrixId()
        {
            return projection_view_matrix_id;
        };

        const glm::mat4 getProjectionMatrix()
        {
            return projection_matrix;
        };

        const glm::mat4 getTransformation();

        Shader_Program& getShaderProgram()
        {
            return shaderProgram;
        }

        void updateCameraTransform();



    };

}

#endif
