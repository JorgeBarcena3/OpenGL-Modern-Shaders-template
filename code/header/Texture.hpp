
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


#include <string>
#include <glm/matrix.hpp>

#include "3DModels/BaseModel3D.hpp"
#include "Shader_Program.hpp"
#include "Color_Buffer_Rgba8888.hpp"


namespace OpenGLRender3D
{

    class Texture
    {

    public:

        static std::shared_ptr< Color_buffers::Color_Buffer_Rgba8888 > load_texture(const std::string& texture_path);

    protected:

        GLuint texture_id;
        bool   texture_is_loaded;

    public:

        Texture() {};
        ~Texture();

    private:

        Texture(const Texture&);


    public:

        bool is_ok() const
        {
            return texture_is_loaded;
        }

        virtual bool bind() const = 0;

    };

}

#endif
