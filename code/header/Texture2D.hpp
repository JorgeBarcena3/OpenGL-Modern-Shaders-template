// File: Texture2D.hpp
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

#ifndef TEXTURE2D_HEADER
#define TEXTURE2D_HEADER

#include <glad/glad.h>
#include "Texture.hpp"

namespace OpenGLRender3D
{
    /**
    * Textura 2D
    */
    class Texture2D: public Texture
    {

    public:

        /**
        * Constructor de la textura 2D
        */
        Texture2D(const std::string& path);        

        /**
        * Heredado de Texture.
        * Bindea la textura
        */
        virtual bool bind() const override;

    };

}

#endif
