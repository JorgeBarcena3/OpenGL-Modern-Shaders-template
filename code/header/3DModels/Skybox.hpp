// File: Skybox.hpp
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

#ifndef CUBE_HEADER
#define CUBE_HEADER

#include "BaseModel3D.hpp"

namespace OpenGLRender3D
{

    /**
    * Determina un cubo donde se renderizará el skybox
    */
    class Skybox : public BaseModel3D
    {
 
    private:

         ShaderProgramHelper::Shader_Program shaderProgram; ///< Shaderprogram id del skybox

         GLint matrix_id;                                   ///< id de la matriz de transformacion del shaderprogram

    public:

        /**
        * Contructor del skybox
        */
        Skybox(const std::string& path, Scene& scene, OpenGLRender3D::OPACITYMODEL op = OpenGLRender3D::OPACITYMODEL::OPAQUE);
        
        /**
        * Destructor del skybox
        */
        ~Skybox();

        /**
        * Heredado de BaseModel3D
        * Renderiza el skybox
        */
        virtual void render() override;

        /**
        * Heredado de BaseModel3D
        * Actualiza la posicion del skybox respecto a la camara
        */
        virtual void update(float time) override;

    };

}

#endif
