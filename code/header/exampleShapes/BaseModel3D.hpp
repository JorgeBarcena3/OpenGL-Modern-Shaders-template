
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef BASESHAPES_HEADER
#define BASESHAPES_HEADER

#include <memory>
#include <vector>
#include <cmath>
#include <SFML/OpenGL.hpp>
#include "../Scene.hpp"
#include "../Transform.hpp"

namespace OpenGLRender3D
{

    class BaseModel3D
    {

    public:

        Transform transform;

        Scene * scene;

        virtual void render() = 0;

        virtual void update() = 0;


    };

}

#endif
