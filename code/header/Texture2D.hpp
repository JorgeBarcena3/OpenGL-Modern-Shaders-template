
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TEXTURE2D_HEADER
#define TEXTURE2D_HEADER

#include <glad/glad.h>
#include "Texture.hpp"

namespace OpenGLRender3D
{

    class Texture2D: public Texture
    {

    public:

        Texture2D(const std::string& path);
        
    };

}

#endif
