
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
        glm::mat4 trasnform_matrix;

        glm::vec3 position;

        glm::vec3 rotation;

        glm::vec3 scale;

    public:

        Transform(glm::vec3 _position = glm::vec3(0, 0, 0), glm::vec3 _rotation = glm::vec3(0, 0, 0), glm::vec3 _scale = glm::vec3(1,1,1))
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

            trasnform_matrix = glm::mat4();

            // Lo empujamos para atras
            trasnform_matrix = glm::translate(trasnform_matrix, position);

            // Lo rotamos
            trasnform_matrix = glm::rotate(trasnform_matrix, rotation[0], glm::vec3(1.f, 0.f, 0.f));
            trasnform_matrix = glm::rotate(trasnform_matrix, rotation[1], glm::vec3(0.f, 1.f, 0.f));
            trasnform_matrix = glm::rotate(trasnform_matrix, rotation[2], glm::vec3(0.f, 0.f, 1.f));

            // Lo escalamos
            trasnform_matrix = glm::scale(trasnform_matrix, scale);

            return trasnform_matrix;
        }

        inline glm::mat4 getInverseMatrix()
        {
            return glm::inverse(getModelViewMatrix());
        }


    };

}

#endif
