// File: PointLight.hpp
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

#ifndef POINTLIGHT_HEADER
#define POINTLIGHT_HEADER

#include "Light.hpp"

namespace OpenGLRender3D
{
    /**
    * Clase que representa una luz puntual
    */
    class PointLight : public Light
    {

    public:

        static GLint light_id;  ///< Cantidad de luces de este tipo que hay


    private:

        glm::vec3 position;     ///< Posicion de la luz

        GLint  positionId;      ///< Id de la posicion en el shader


    public:

        /**
        * Contructor por defecto
        */
        PointLight(glm::vec3 pos, Scene& scene) : position(pos), Light(scene)
        {
                
        }

        /**
        * Posicion de la luz
        */
        void setPosition(glm::vec3 _direction)
        {
            position = _direction;
        }

        /**
        * Devuelve la posicion de la luz
        */
        glm::vec3 getPosition()
        {
            return position;
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
