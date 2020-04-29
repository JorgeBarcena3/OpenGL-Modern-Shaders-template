
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TRANSFORM_HEADER
#define TRANSFORM_HEADER

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "exampleShapes/BaseModel3D.hpp"
#include <string>
#include "Shader_Program.hpp"
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective


namespace OpenGLRender3D
{

    using namespace shaderToolkit;

    class Transform
    {
    private:

        // Matriz de coordenadas de modelo
        glm::mat4 model_view_matrix;

        glm::vec3 position;

        glm::vec3 rotation;

        glm::vec3 scale;

    public:

        Transform(glm::vec3 _position = glm::vec3(0, 0, -20), glm::vec3 _rotation = glm::vec3(0, 0, 0), glm::vec3 _scale = glm::vec3(1,1,1))
        {
            position = _position;
            rotation = _rotation;
            scale = _scale;

        }

        inline glm::vec3 getPosition()
        {
            return position;
        }

        inline glm::vec3 getRotation()
        {
            return rotation;
        }

        inline glm::vec3 getScale()
        {
            return scale;
        }

        inline void setPosition(glm::vec3 _v)
        {
            position = _v;
        }
        inline void setRotation(glm::vec3 _v)
        {
            rotation = _v;
        }

        inline void setScale(glm::vec3 _v)
        {
            scale = _v;
        }

        glm::mat4 getModelViewMatrix()
        {

            model_view_matrix = glm::mat4();

            // Lo empujamos para atras
            model_view_matrix = glm::translate(model_view_matrix, position);

            // Lo rotamos
            model_view_matrix = glm::rotate(model_view_matrix, rotation[0], glm::vec3(1.f, 0.f, 0.f));
            model_view_matrix = glm::rotate(model_view_matrix, rotation[1], glm::vec3(0.f, 1.f, 0.f));
            model_view_matrix = glm::rotate(model_view_matrix, rotation[2], glm::vec3(0.f, 0.f, 1.f));

            // Lo escalamos
            model_view_matrix = glm::scale(model_view_matrix, scale);

            return model_view_matrix;
        }


    };

}

#endif
