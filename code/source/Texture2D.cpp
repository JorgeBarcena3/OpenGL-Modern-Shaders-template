#include "..\header\Texture2D.hpp"
#include <stdexcept>


extern "C"
{
#include <targa.h>
}

OpenGLRender3D::Texture2D::Texture2D(const std::string& path)
{

    texture_is_loaded = false;

    std::shared_ptr< Color_buffers::Color_Buffer_Rgba8888 > texture;

    texture = load_texture(path);

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexImage2D
    (
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        texture->get_width(),
        texture->get_height(),
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        texture->colors()
    );

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    texture_is_loaded = true;

}

bool OpenGLRender3D::Texture2D::bind() const
{
    return texture_is_loaded ? glBindTexture(GL_TEXTURE_2D, texture_id), true : false;
}
