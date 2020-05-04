#include "..\header\Texture.hpp"
#include <SOIL.h>

extern "C"
{
#include <targa.h>
}

OpenGLRender3D::Texture::~Texture()
{
    if (texture_is_loaded)
    {
        glDeleteTextures(1, &texture_id);
    }
}


std::shared_ptr<Color_buffers::Color_Buffer_Rgba8888> OpenGLRender3D::Texture::load_texture(const std::string& texture_path)
{
    std::shared_ptr< Color_buffers::Color_Buffer_Rgba8888 > buffer;

    try {
        // Se carga el archivo TGA:
        if (texture_path.find(".tga") != std::string::npos)
        {
            tga_image loaded_image;

            if (tga_read(&loaded_image, texture_path.c_str()) == TGA_NOERR)
            {
                // Se crea un búfer con el formato de píxel adecuado:

                buffer.reset(new Color_buffers::Color_Buffer_Rgba8888(loaded_image.width, loaded_image.height));

                // Se convierte el búfer de la imagen cargada al formato de píxel adecuado:

                tga_convert_depth(&loaded_image, buffer->bits_per_color());
                tga_swap_red_blue(&loaded_image);

                Color_buffers::Color_Buffer_Rgba8888::Color* loaded_image_pixels = reinterpret_cast<Color_buffers::Color_Buffer_Rgba8888::Color*>(loaded_image.image_data);
                Color_buffers::Color_Buffer_Rgba8888::Color* loaded_image_pixels_end = loaded_image_pixels + loaded_image.width * loaded_image.height;
                Color_buffers::Color_Buffer_Rgba8888::Color* texture_buffer_pixels = buffer->colors();

                while (loaded_image_pixels < loaded_image_pixels_end)
                {
                    *texture_buffer_pixels++ = *loaded_image_pixels++;
                }

                tga_free_buffers(&loaded_image);
            }
        }
        else
        {

            int width, height;

            GLubyte* image = SOIL_load_image(texture_path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

            buffer.reset(new Color_buffers::Color_Buffer_Rgba8888(width, height));

            Color_buffers::Color_Buffer_Rgba8888::Color* loaded_image_pixels = reinterpret_cast<Color_buffers::Color_Buffer_Rgba8888::Color*>(image);
            Color_buffers::Color_Buffer_Rgba8888::Color* loaded_image_pixels_end = loaded_image_pixels + width * height;
            Color_buffers::Color_Buffer_Rgba8888::Color* texture_buffer_pixels = buffer->colors();

            while (loaded_image_pixels < loaded_image_pixels_end)
            {
                *texture_buffer_pixels++ = *loaded_image_pixels++;
            }

            SOIL_free_image_data(image);


        }
    }
    catch(const std::exception & e)
    {

        tga_image loaded_image;

        if (tga_read(&loaded_image, ConfigOptions::ConfigPaths::configSettingsMap["texture_default_path"].c_str()) == TGA_NOERR)
        {
            // Se crea un búfer con el formato de píxel adecuado:

            buffer.reset(new Color_buffers::Color_Buffer_Rgba8888(loaded_image.width, loaded_image.height));

            // Se convierte el búfer de la imagen cargada al formato de píxel adecuado:

            tga_convert_depth(&loaded_image, buffer->bits_per_color());
            tga_swap_red_blue(&loaded_image);

            Color_buffers::Color_Buffer_Rgba8888::Color* loaded_image_pixels = reinterpret_cast<Color_buffers::Color_Buffer_Rgba8888::Color*>(loaded_image.image_data);
            Color_buffers::Color_Buffer_Rgba8888::Color* loaded_image_pixels_end = loaded_image_pixels + loaded_image.width * loaded_image.height;
            Color_buffers::Color_Buffer_Rgba8888::Color* texture_buffer_pixels = buffer->colors();

            while (loaded_image_pixels < loaded_image_pixels_end)
            {
                *texture_buffer_pixels++ = *loaded_image_pixels++;
            }

            tga_free_buffers(&loaded_image);
        }

    }

    return buffer;
}
