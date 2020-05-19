// File: SFMLApplication.hpp
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

#ifndef SFMLAPPLICATION_HEADER
#define SFMLAPPLICATION_HEADER


#include <string>

namespace sf
{
    class Window;
    class Mouse;
}

namespace OpenGLRender3D
{

    class Scene;


    /**
    * Abstraccion para utilizar la herramiento con la libreria SFML
    */
    class SFMLApplication
    {

    private:


        sf::Window* window; ///< Window de la aplicacion

        Scene * myScene;    ///< Escena de la herramienta

    public:


        /**
        * Constructor por defecto
        */
        SFMLApplication(std::string path);

        /**
        * Destructor por defecto
        */
        ~SFMLApplication();

        /**
        * Inicia la escena por defecto
        */
        void start();

    };

}

#endif
