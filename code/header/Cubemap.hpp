
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CUBEMAP_HEADER
#define CUBEMAP_HEADER

#include <glad/glad.h>
#include "Texture.hpp"

namespace OpenGLRender3D
{

    class Cubemap : public Texture
    {

    public:

        Cubemap(const std::string& path);
        
    };

}

#endif
