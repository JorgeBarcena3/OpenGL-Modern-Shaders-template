
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef EXAMPLESHAPES_HEADER
#define EXAMPLESHAPES_HEADER

#include <memory>
#include <vector>
#include <cmath>
#include <SFML/OpenGL.hpp>

namespace exampleShapes
{

    class ExampleShape
    {

    public:
        
        virtual void render() = 0;

    };

}

#endif
