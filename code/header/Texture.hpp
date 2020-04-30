
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <glad/glad.h>
#include "exampleShapes/BaseModel3D.hpp"
#include <string>
#include "Shader_Program.hpp"
#include <glm/matrix.hpp>
#include "Color_Buffer_Rgba8888.hpp"

namespace OpenGLRender3D
{

    class Texture
    {
 

    protected:

        GLuint texture_id;
        bool   texture_is_loaded;

    public:

        Texture() {};
        ~Texture();

    private:

        Texture(const Texture&);

    protected:

        std::shared_ptr< Color_buffers::Color_Buffer_Rgba8888 > load_texture(const std::string& texture_path);

    public:

        bool is_ok() const
        {
            return texture_is_loaded;
        }

        virtual bool bind() const = 0;

    };

}

#endif
