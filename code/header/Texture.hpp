// File: Texture.hpp
// Author: Jorge B�rcena Lumbreras

// � Copyright (C) 2020  Jorge B�rcena Lumbreras

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

#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER


#include <string>
#include <glm/matrix.hpp>

#include "3DModels/BaseModel3D.hpp"
#include "Shader_Program.hpp"
#include "Color_Buffer_Rgba8888.hpp"


namespace OpenGLRender3D
{

    /**
    * Clase base de textura
    */
    class Texture
    {

    public:

        /**
        * Carga una textura en la GPU
        */
        static std::shared_ptr< Color_buffers::Color_Buffer_Rgba8888 > load_texture(const std::string& texture_path);

    protected:


        GLuint texture_id;          ///< Id de la textura 

        bool   texture_is_loaded;   ///< La textura esta cargada en la GPU

    public:

        /**
        * Constructor por defecto
        */
        Texture() {};

        /**
        * Destructor por defecto
        */
        ~Texture();

    private:

        /**
        * Constructor por defecto
        */
        Texture(const Texture&);


    public:

        /**
        * Determina si esta cargada la textura
        */
        bool is_ok() const
        {
            return texture_is_loaded;
        }

        /**
        * Bindea la textura
        */
        virtual bool bind() const = 0;

    };

}

#endif
