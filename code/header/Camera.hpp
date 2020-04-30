
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
#include "exampleShapes/BaseModel3D.hpp"


namespace OpenGLRender3D
{

    using namespace shaderToolkit;

    class Camera
    {

    public:

        Transform transform;

    private:

        GLint  projection_view_matrix_id;
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



    };

}

#endif
