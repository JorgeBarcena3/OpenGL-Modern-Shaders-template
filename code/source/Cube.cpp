
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "../header/exampleShapes/Cube.hpp"
#include <SFML/OpenGL.hpp>
#include "../header/Color_Buffer_Rgba8888.hpp"

extern "C"
{
    #include <targa.h>
}

namespace exampleShapes
{

    const GLfloat Cube::coordinates[][3] =
    {
        { -1.f, +1.f, +1.f },   // 0
        { +1.f, +1.f, +1.f },   // 1
        { +1.f, -1.f, +1.f },   // 2
        { -1.f, -1.f, +1.f },   // 3
        { -1.f, +1.f, -1.f },   // 4
        { -1.f, +1.f, +1.f },   // 5
        { -1.f, -1.f, +1.f },   // 6
        { -1.f, -1.f, -1.f },   // 7
        { +1.f, +1.f, -1.f },   // 8
        { -1.f, +1.f, -1.f },   // 9
        { -1.f, -1.f, -1.f },   // 10
        { +1.f, -1.f, -1.f },   // 11
        { +1.f, +1.f, +1.f },   // 12
        { +1.f, +1.f, -1.f },   // 13
        { +1.f, -1.f, -1.f },   // 14
        { +1.f, -1.f, +1.f },   // 15
        { -1.f, -1.f, +1.f },   // 16
        { +1.f, -1.f, +1.f },   // 17
        { +1.f, -1.f, -1.f },   // 18
        { -1.f, -1.f, -1.f },   // 19
        { -1.f, +1.f, -1.f },   // 20
        { +1.f, +1.f, -1.f },   // 21
        { +1.f, +1.f, +1.f },   // 22
        { -1.f, +1.f, +1.f },   // 23
    };

    const GLfloat Cube::normals[][3] =
    {
        {  0.f,  0.f, +1.f },   // 0
        {  0.f,  0.f, +1.f },   // 1
        {  0.f,  0.f, +1.f },   // 2
        {  0.f,  0.f, +1.f },   // 3
        { -1.f,  0.f,  0.f },   // 4
        { -1.f,  0.f,  0.f },   // 5
        { -1.f,  0.f,  0.f },   // 6
        { -1.f,  0.f,  0.f },   // 7
        {  0.f,  0.f, -1.f },   // 8
        {  0.f,  0.f, -1.f },   // 9
        {  0.f,  0.f, -1.f },   // 10
        {  0.f,  0.f, -1.f },   // 11
        { +1.f,  0.f,  0.f },   // 12
        { +1.f,  0.f,  0.f },   // 13
        { +1.f,  0.f,  0.f },   // 14
        { +1.f,  0.f,  0.f },   // 15
        {  0.f, -1.f,  0.f },   // 16
        {  0.f, -1.f,  0.f },   // 17
        {  0.f, -1.f,  0.f },   // 18
        {  0.f, -1.f,  0.f },   // 19
        {  0.f, +1.f,  0.f },   // 20
        {  0.f, +1.f,  0.f },   // 21
        {  0.f, +1.f,  0.f },   // 22
        {  0.f, +1.f,  0.f },   // 23
    };

    const GLfloat Cube::tex_coords[][2] =
    {
        { 0.f, 0.f },           // 0
        { 1.f, 0.f },           // 1
        { 1.f, 1.f },           // 2
        { 0.f, 1.f },           // 3
        { 0.f, 0.f },           // 4
        { 1.f, 0.f },           // 5
        { 1.f, 1.f },           // 6
        { 0.f, 1.f },           // 7
        { 0.f, 0.f },           // 8
        { 1.f, 0.f },           // 9
        { 1.f, 1.f },           // 10
        { 0.f, 1.f },           // 11
        { 0.f, 0.f },           // 12
        { 1.f, 0.f },           // 13
        { 1.f, 1.f },           // 14
        { 0.f, 1.f },           // 15
        { 0.f, 0.f },           // 16
        { 1.f, 0.f },           // 17
        { 1.f, 1.f },           // 18
        { 0.f, 1.f },           // 19
        { 0.f, 0.f },           // 20
        { 1.f, 0.f },           // 21
        { 1.f, 1.f },           // 22
        { 0.f, 1.f },           // 23
    };

    const GLubyte Cube::indices[][3] =
    {
        {  1,  0,  3 },         // front
        {  1,  3,  2 },
        {  5,  4,  7 },         // left
        {  5,  7,  6 },
        {  9,  8, 11 },         // back
        {  9, 11, 10 },
        { 13, 12, 15 },         // right
        { 13, 15, 14 },
        { 17, 16, 19 },         // top
        { 17, 19, 18 },
        { 20, 23, 22 },         // bottom
        { 20, 22, 21 },
    };

    Cube::Cube(const char * texture_path)
    :
        has_texture(false)
    {
        if (texture_path != 0)
        {
            std::auto_ptr< Texture > texture = load_texture (texture_path);

            has_texture = texture.get () != 0;

            if (has_texture)
            {
                // Se habilitan las texturas, se genera un id para un búfer de textura,
                // se selecciona el búfer de textura creado y se configuran algunos de
                // sus parámetros:

                glEnable        (GL_TEXTURE_2D );
                glGenTextures   (1, &texture_id);
                glBindTexture   (GL_TEXTURE_2D, texture_id);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

                // Se suben los colores de la textura a la memoria de vídeo:

                glTexImage2D
                (
                    GL_TEXTURE_2D,
                    0,
                    GL_RGBA,
                    texture->get_width  (),
                    texture->get_height (),
                    0,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    texture->colors ()
                );
            }
        }
    }

    Cube::~Cube()
    {
        if (has_texture)
        {
            glDeleteTextures (1, &texture_id);
        }
    }

    void Cube::render ()
    {
        if (has_texture)
        {
            glEnableClientState (GL_TEXTURE_COORD_ARRAY);           // Se habilitan los arrays de coordenadas de textura
            glBindTexture       (GL_TEXTURE_2D,  texture_id);       // Se selecciona la textura
            glTexCoordPointer   (2, GL_FLOAT, 0, tex_coords);       // Se carga el array de coordenadas de textura
        }

        glEnableClientState (GL_VERTEX_ARRAY);
        glEnableClientState (GL_NORMAL_ARRAY);

        glVertexPointer (3, GL_FLOAT, 0, coordinates);
        glNormalPointer (   GL_FLOAT, 0, normals    );

        glDrawElements  (GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_BYTE, indices);
    }

    std::auto_ptr< Texture > Cube::load_texture (const char * texture_file_path)
    {
        std::auto_ptr< Texture > texture;
        tga_image                loaded_image;

        if (tga_read (&loaded_image, texture_file_path) == TGA_NOERR)
        {
            // Si se ha podido cargar la imagen desde el archivo, se crea un búfer para una textura:

            texture.reset (new Texture(loaded_image.width, loaded_image.height));

            // Se convierte el formato de píxel de la imagen cargada a RGBA8888:

            tga_convert_depth (&loaded_image, texture->bits_per_color ());
            tga_swap_red_blue (&loaded_image);

            // Se copian los pixels del búfer de la imagen cargada al búfer de la textura:

            Texture::Color * loaded_image_pixels     = reinterpret_cast< Texture::Color * >(loaded_image.image_data);
            Texture::Color * loaded_image_pixels_end = loaded_image_pixels + loaded_image.width * loaded_image.height;
            Texture::Color * image_buffer_pixels     = texture->colors ();

            while (loaded_image_pixels <  loaded_image_pixels_end)
            {
                *image_buffer_pixels++ = *loaded_image_pixels++;
            }

            tga_free_buffers (&loaded_image);
        }

        return (texture);
    }

}
