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
    tga_image                loaded_image;

    if (tga_read(&loaded_image, path.c_str()) == TGA_NOERR)
    {
        // Si se ha podido cargar la imagen desde el archivo, se crea un búfer para una textura:

        texture.reset(new Color_buffers::Color_Buffer_Rgba8888(loaded_image.width, loaded_image.height));

        // Se convierte el formato de píxel de la imagen cargada a RGBA8888:

        tga_convert_depth(&loaded_image, texture->bits_per_color());
        tga_swap_red_blue(&loaded_image);

        // Se copian los pixels del búfer de la imagen cargada al búfer de la textura:

        Color_buffers::Color_Buffer_Rgba8888::Color* loaded_image_pixels = reinterpret_cast<Color_buffers::Color_Buffer_Rgba8888::Color*>(loaded_image.image_data);
        Color_buffers::Color_Buffer_Rgba8888::Color* loaded_image_pixels_end = loaded_image_pixels + loaded_image.width * loaded_image.height;
        Color_buffers::Color_Buffer_Rgba8888::Color* image_buffer_pixels = texture->colors();

        while (loaded_image_pixels < loaded_image_pixels_end)
        {
            *image_buffer_pixels++ = *loaded_image_pixels++;
        }

        tga_free_buffers(&loaded_image);
    }
    else
        throw std::exception(std::string("No se ha podido cargar la textura desde la ruta: " + path).c_str());


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
