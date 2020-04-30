#include "../header/Cubemap.hpp"


OpenGLRender3D::Cubemap::Cubemap(const std::string& path) 
{
    texture_is_loaded = false;

    // Se intentan cargar los mapas de bits de todas las caras:

    std::vector< std::shared_ptr< Color_buffers::Color_Buffer_Rgba8888 > > texture_sides(6);

    for (size_t texture_index = 0; texture_index < 6; texture_index++)
    {
        texture_sides[texture_index] = load_texture(path + char('0' + texture_index) + ".tga");

        if (!texture_sides[texture_index])
        {
            return;
        }
    }

    // Se crea un objeto de textura:

    glEnable(GL_TEXTURE_CUBE_MAP);

    glGenTextures(1, &texture_id);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

    // Se configura la textura: escalado suavizado, clamping de coordenadas (s,t) hasta el borde:

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Se envían los mapas de bits a la GPU:

    static const GLenum texture_target[] =
    {
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    };

    for (size_t texture_index = 0; texture_index < 6; texture_index++)
    {
        Color_buffers::Color_Buffer_Rgba8888& texture = *texture_sides[texture_index];

        glTexImage2D
        (
            texture_target[texture_index],
            0,
            GL_RGBA,
            texture.get_width(),
            texture.get_height(),
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            texture.colors()
        );
    }

    texture_is_loaded = true;
}