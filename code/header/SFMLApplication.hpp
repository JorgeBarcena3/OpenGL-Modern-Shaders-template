
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Copyright © 2014+ Ángel Rodríguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SFMLAPPLICATION_HEADER
#define SFMLAPPLICATION_HEADER

#include <SFML/Window.hpp>
#include "Scene.hpp"

namespace OpenGLRender3D
{

    class SFMLApplication
    {

    private:

        sf::Window * window;

        Scene * myScene;

    public:

        SFMLApplication();

        ~SFMLApplication();

        void start();

    };

}

#endif
