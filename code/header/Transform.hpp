
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

#include <string>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective

#include "3DModels/BaseModel3D.hpp"
#include "Shader_Program.hpp"


namespace OpenGLRender3D
{

    class Transform
    {
    public:

        Transform * parent;

    private:

        // Matriz de coordenadas de modelo
        glm::mat4 transform_matrix;

        glm::vec3 position;

        glm::vec3 rotation;

        glm::vec3 scale;

    public:

        Transform(glm::vec3 _position = glm::vec3(0, 0, 0), glm::vec3 _rotation = glm::vec3(0, 0, 0), glm::vec3 _scale = glm::vec3(1, 1, 1))
        {
            position = _position;
            rotation = _rotation;
            scale = _scale;
            parent = nullptr;

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

            transform_matrix = glm::mat4();

            // Lo empujamos para atras
            transform_matrix = glm::translate(transform_matrix, position);

            // Lo rotamos
            transform_matrix = glm::rotate(transform_matrix, glm::radians(rotation[0]), glm::vec3(1.f, 0.f, 0.f));
            transform_matrix = glm::rotate(transform_matrix, glm::radians(rotation[1]), glm::vec3(0.f, 1.f, 0.f));
            transform_matrix = glm::rotate(transform_matrix, glm::radians(rotation[2]), glm::vec3(0.f, 0.f, 1.f));

            // Lo escalamos
            transform_matrix = glm::scale(transform_matrix, scale);

            if (parent != nullptr)
            {
                transform_matrix = parent->getModelViewMatrix() * transform_matrix;
            }


            return transform_matrix;
        }

        inline glm::mat4 getInverseMatrix()
        {
            return glm::inverse(transform_matrix);
        }

        inline glm::vec3 getFordwardVector()
        {

            glm::vec4 a = transform_matrix * glm::vec4(0, 0, -1, 0);
            return glm::vec3(a[0], a[1], a[2]);
        }

        inline glm::vec3 getRightVector()
        {

            glm::vec4 a = transform_matrix * glm::vec4(1, 0, 0, 0);
            return glm::vec3(a[0], a[1], a[2]);
        }
        
        inline glm::vec3 getUpVector()
        {

            glm::vec4 a = transform_matrix * glm::vec4(0, 1, 0, 0);
            return glm::vec3(a[0], a[1], a[2]);
        }

        inline void addParent(Transform* transform)
        {
            parent = (transform);
        }

        
    };

}

#endif
