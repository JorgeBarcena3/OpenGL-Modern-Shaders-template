// File: Transfom.hpp
// Author: Jorge Bárcena Lumbreras

// © Copyright (C) 2020  Jorge Bárcena Lumbreras

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef TRANSFORM_HEADER
#define TRANSFORM_HEADER

#include <string>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective

#include "3DModels/BaseModel3D.hpp"
#include "Shader_Program.hpp"


namespace OpenGLRender3D
{

    /**
    * Clase que maneja el transform de un modelo
    */
    class Transform
    {

    public:

        Transform * parent;         ///< Transform del padre

    private:

        glm::mat4 transform_matrix; ///<  Matriz de la transformacion

        glm::vec3 position;         ///< Posicion del transform

        glm::vec3 rotation;         ///< Rotacion

        glm::vec3 scale;            ///< Escala

    public:

        /**
        * Contructor por defecto
        */
        Transform(glm::vec3 _position = glm::vec3(0, 0, 0), glm::vec3 _rotation = glm::vec3(0, 0, 0), glm::vec3 _scale = glm::vec3(1, 1, 1))
        {
            position = _position;
            rotation = _rotation;
            scale = _scale;
            parent = nullptr;

        }

        /**
        * Devuelve la posicion de la entidad
        */
        inline glm::vec3 getPosition()
        {
            return position;
        }

        /**
        * Devuelve la rotacion de la entidad
        */
        inline glm::vec3 getRotation()
        {
            return rotation;
        }

        /**
        * Devuelve la escala de la entidad
        */
        inline glm::vec3 getScale()
        {
            return scale;
        }

        /**
        * Determina la posicion de la entidad
        */
        inline void setPosition(glm::vec3 _v)
        {
            position = _v;
        }

        /**
        * Determina la rotacion de la entidad
        */
        inline void setRotation(glm::vec3 _v)
        {
            rotation = _v;
        }

        /**
        * Determina la escala de la entidad
        */
        inline void setScale(glm::vec3 _v)
        {
            scale = _v;
        }

        /**
        * Devuelve la matriz del modelo
        */
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

        /**
        * Devuelve la matriz inversa del modelo
        */
        inline glm::mat4 getInverseMatrix()
        {
            return glm::inverse(transform_matrix);
        }

        /**
        * Añade un padre al transform
        */
        inline void addParent(Transform* transform)
        {
            parent = (transform);
        }

        
    };

}

#endif
