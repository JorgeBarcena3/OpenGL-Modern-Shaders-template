
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Copyright � 2014+ �ngel Rodr�guez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  Started by �ngel on april of 2014                                          *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SFMLAPPLICATION_HEADER
#define SFMLAPPLICATION_HEADER

#include <string>

namespace sf
{
    class Window;
}

namespace OpenGLRender3D
{

    class Scene;

    class SFMLApplication
    {

    private:

        sf::Window* window;

        Scene * myScene;

    public:

        SFMLApplication(std::string path);

        ~SFMLApplication();

        void start();

    };

}

#endif
