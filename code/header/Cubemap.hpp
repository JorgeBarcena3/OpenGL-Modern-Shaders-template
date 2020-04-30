
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by �ngel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CUBEMAP_HEADER
#define CUBEMAP_HEADER

#include "Texture.hpp"
#include <glad/glad.h>

namespace OpenGLRender3D
{

    class Cubemap : public Texture
    {

    public:

        Cubemap(const std::string& path);
        

        // Heredado v�a Texture
        virtual bool bind() const override;

    };

}

#endif
