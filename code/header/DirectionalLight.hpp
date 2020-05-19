// File: DirectionalLight.hpp
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

#ifndef DIRECTIONALLIGHT_HEADER
#define DIRECTIONALLIGHT_HEADER

#include "Light.hpp"

namespace OpenGLRender3D
{

    /**
    * Clase que representa una luz direccional
    */
    class DirectionalLight : public Light
    {

    public:

        static GLint light_id; ///< Id de la luz actual

    private:

        glm::vec3 direction; ///< Direccion de la luz

        GLint directionId;   ///< Id de la direccion de la luz en el shaderprogram

    public:

        /**
        * Constructor de la luz
        */
        DirectionalLight(glm::vec3 _direction, Scene& scene) : direction(glm::normalize(_direction)), Light(scene)
        {

        }

        /**
        * Deetermina la direccion de la luz
        */
        void setDirection(glm::vec3 _direction)
        {
            direction = _direction;
        }

        /**
        * Devuelve la direccion de la luz
        */
        glm::vec3 getDirection()
        {
            return direction;
        }

        /**
        * Hereda de light.
        * Setea todas las variables uniformes
        */
        virtual void setUniformVariables(ShaderProgramHelper::Shader_Program& shader) override;

        /**
        * Hereda de light.
        * Obtiene los id de la variable de las luces
        */
        virtual void getUniformId(ShaderProgramHelper::Shader_Program& shader, std::string lightId) override;

    };

}

#endif
