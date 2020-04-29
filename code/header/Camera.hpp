
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "exampleShapes/BaseModel3D.hpp"
#include <string>
#include "Shader_Program.hpp"
#include <glm/matrix.hpp>

namespace OpenGLRender3D
{

    using namespace shaderToolkit;

    class Camera
    {
    private:

        static const std::string   vertex_shader_code;
        static const std::string fragment_shader_code;

        GLint  projection_view_matrix_id;
        glm::mat4 projection_matrix;

    public:

        Camera(int width, int height);

        void   update(float time);
        void   render();
        void   resize(int width, int height);
        bool   uploadUniformVariable(const char* name, float value);
        bool   uploadUniformVariable(const char* name, Vector3f value);

        const GLint getProjectionMatrixId()
        {
            return projection_view_matrix_id;
        };

        const glm::mat4 getProjectionMatrix()
        {
            return projection_matrix;
        };

        

    private:

        Shader_Program shaderProgram;
    };

}

#endif
