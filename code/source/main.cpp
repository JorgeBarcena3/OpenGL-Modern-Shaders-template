
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "../header/SFMLApplication.hpp"
#include <iostream>


int main(int argc, char* argv[])
{
    std::string path = "./scene.xml";
    
    if(argc == 3)
    {
        path = (!strcmp(argv[1], "--scene")) ? argv[2] : "./scene.xml";
    }

    OpenGLRender3D::SFMLApplication app(path);
    app.start();

    return 0;
}
