
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge Barcena on March of 2020                                  *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "../../header/exampleShapes/Malla.hpp"
#include <SFML/OpenGL.hpp>
#include <cmath>
#include <glm/vec3.hpp>
#include "../../header/Color_Buffer_Rgba8888.hpp"
#include "../../header/Camera.hpp";
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

extern "C"
{
#include <targa.h>

}

#define PI2 2.0 * 3.141592

namespace OpenGLRender3D
{

    Malla::Malla(float _width, float _height, int _vertex_count, Scene& _scene, std::string path)
    {

        transform = Transform(glm::vec3(0,0,-20), glm::vec3(0,0,0), glm::vec3(1,1,1));
        width = _width;
        height = _height;
        vertex_count = _vertex_count;
        scene = &_scene;

        std::vector< GLfloat > coordinates;
        std::vector< GLfloat > normals;
        std::vector< GLfloat > colors;
        std::vector< GLfloat > tx;

        // Se generan índices para los VBOs del cubo:

        glGenBuffers(VBO_COUNT, vbo_ids);
        glGenVertexArrays(1, &vao_id);

        // Se activa el VAO del cubo para configurarlo:

        glBindVertexArray(vao_id);

        createVertices(coordinates, normals, tx);
        createColors(colors, coordinates);
        if (!path.empty())
        {
            setHeightCoordinates(coordinates, tx, path);
        }


        /**********************
        ** DATOS DE VERTICES **
        ***********************/

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
        glBufferData(GL_ARRAY_BUFFER, coordinates.size() * sizeof(GLfloat), &coordinates[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        /*******************
        ** DATOS DE COLOR **
        ********************/

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

        /**********************
        ** DATOS DE NORMALES **
        ***********************/

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[NORMALS_VBO]);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

        /*********************
        ** DATOS DE TEXTURA **
        **********************/

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[TEXTURE_COORD]);
        glBufferData(GL_ARRAY_BUFFER, tx.size() * sizeof(GLfloat), &tx[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);

        /*********************
        ** DATOS DE INDICES **
        **********************/

        createIndices(coordinates);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_IBO]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    Malla::~Malla()
    {
        // Se liberan los VBOs y el VAO usados:

        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers(VBO_COUNT, vbo_ids);
    }

    void Malla::setHeightCoordinates(std::vector< GLfloat >& coordinates, std::vector< GLfloat >& tx, std::string path)
    {
        std::shared_ptr< example::Color_Buffer_Rgba8888 > texture;


        tga_image loaded_image;

        if (tga_read(&loaded_image, path.c_str()) == TGA_NOERR)
        {
            // Si se ha podido cargar la imagen desde el archivo, se crea un búfer para una textura:

            texture.reset(new example::Color_Buffer_Rgba8888(loaded_image.width, loaded_image.height));

            // Se convierte el formato de píxel de la imagen cargada a RGBA8888:

            tga_convert_depth(&loaded_image, texture->bits_per_color());
            tga_swap_red_blue(&loaded_image);

            // Se copian los pixels del búfer de la imagen cargada al búfer de la textura:

            example::Color_Buffer_Rgba8888::Color* loaded_image_pixels = reinterpret_cast<example::Color_Buffer_Rgba8888::Color*>(loaded_image.image_data);
            example::Color_Buffer_Rgba8888::Color* loaded_image_pixels_end = loaded_image_pixels + loaded_image.width * loaded_image.height;
            example::Color_Buffer_Rgba8888::Color* image_buffer_pixels = texture->colors();

            while (loaded_image_pixels < loaded_image_pixels_end)
            {
                *image_buffer_pixels++ = *loaded_image_pixels++;
            }

            tga_free_buffers(&loaded_image);
        }
        else
        {
            return;
        }


        float max_height = 5;
        int texture_index = 0;

        // Cuanto mas alto mas blanco
        for (size_t i = 0; i < coordinates.size(); i += 3)
        {
            int pixel_x = texture->get_width() * tx[texture_index];
            int pixel_y = texture->get_height() * tx[texture_index + 1];

            auto pixel = texture->colors()[texture->offset_at(pixel_x, pixel_y)];

            float grey_scale = pixel.data.component.r;

            float height = (grey_scale * max_height) / 255;

            coordinates[i + 1] = height;

            texture_index += 2;
        }
    }

    void Malla::createVertices(std::vector< GLfloat >& coordinates, std::vector< GLfloat >& normals, std::vector< GLfloat >& tx)
    {


        int vertexCount = vertex_count * vertex_count;
        int faceCount = (vertex_count - 1) * (vertex_count - 1) * 2;
        // Create the vertices.

        float halfWidth = 0.5f * width;
        float halfDepth = 0.5f * height;

        float dx = width / (vertex_count - 1);
        float dz = height / (vertex_count - 1);

        float du = 1.0f / (vertex_count - 1);
        float dv = 1.0f / (vertex_count - 1);


        for (GLfloat i = 0.0f; i < vertex_count; ++i)
        {
            GLfloat z = halfDepth - i * dz;
            for (GLfloat j = 0.0f; j < vertex_count; ++j)
            {
                //code
                GLfloat x = -halfWidth + j * dx;

                coordinates.push_back(x);
                coordinates.push_back(0.0f);
                coordinates.push_back(z);

                normals.push_back(0); // x
                normals.push_back(1); // y
                normals.push_back(0); // z

                tx.push_back(j * du);
                tx.push_back(i * dv);

            }
        }

    }

    void Malla::createIndices(std::vector< GLfloat >& coordinates)
    {

        GLfloat offset_y = 1;
        GLfloat offset_x = 0;
        int index = 0;
        int vertex_triangles = ( (vertex_count - 1) * (vertex_count - 1) * 2 );


        GLuint offset = 0;
        for (GLuint i = 0; i < vertex_count - 1; ++i)
        {
            for (GLuint j = 0; j < vertex_count - 1; ++j)
            {
                indices.push_back(i * vertex_count + j);
                indices.push_back(i * vertex_count + j + 1);
                indices.push_back((i + 1) * vertex_count + j);

                indices.push_back((i + 1) * vertex_count + j);
                indices.push_back(i * vertex_count + j + 1);
                indices.push_back((i + 1) * vertex_count + j + 1);


            }
        }
    }

    void Malla::createColors(std::vector< GLfloat >& colors, std::vector< GLfloat >& coordinates)
    {
        colors.resize(coordinates.size());

        for (size_t i = 0; i < colors.size(); i += 3)
        {
            colors[i] = (0.5f);
            colors[i + 1] = (0.25f);
            colors[i + 2] = (1);
        }
    }
          
    void Malla::update()
    {
        static float angle = 0;
        angle += 0.0f;

        transform.setRotation(glm::vec3(angle, 0, 0));
    }

    void Malla::render()
    {
        
        glm::mat4 projection_view_matrix = scene->getMainCamera()->getProjectionMatrix() * scene->getMainCamera()->transform.getInverseMatrix() *  transform.getModelViewMatrix();
        glUniformMatrix4fv(scene->getMainCamera()->getProjectionMatrixId(), 1, GL_FALSE, glm::value_ptr(projection_view_matrix));

        // Se selecciona el VAO que contiene los datos del objeto y se dibujan sus elementos:

        glBindVertexArray(vao_id);
        glDrawElements(GL_TRIANGLES, indices.size() * sizeof(GLuint), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }


}
