
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge Barcena on March of 2020                                  *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define GLM_FORCE_RADIANS

#include <cmath>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

#include "../../header/3DModels/Malla.hpp"
#include "../../header/Color_Buffer_Rgba8888.hpp"
#include "../../header/Texture2D.hpp"
#include "../../header/Camera.hpp"

extern "C"
{
#include <targa.h>

}

#define PI2 2.0 * 3.141592

namespace OpenGLRender3D
{

    Malla::Malla(float _width, float _height, float _max_height, int _vertex_count, Scene& _scene, OpenGLRender3D::OPACITYMODEL op, std::string path, std::string tx_path) :
        BaseModel3D(op, _scene)
    {
        setDefaultMaterial(tx_path);

        transform = Transform(glm::vec3(0, 0, -20), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
        width = _width;
        height = _height;
        vertex_count = _vertex_count;
        max_height = _max_height;

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
            setHeightCoordinates(coordinates, normals, tx, path);
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

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[TEXTURE_VBO]);
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

        modelMatrixTransformationId = scene->getMainCamera()->getShaderProgram().get_uniform_id(ConfigOptions::ConfigPaths::configSettingsMap["shader_model_matrix"].c_str());
    }

    Malla::~Malla()
    {
       
    }

    void Malla::setHeightCoordinates(std::vector< GLfloat >& coordinates, std::vector< GLfloat >& normals, std::vector< GLfloat >& tx, std::string path)
    {
        std::shared_ptr< Color_buffers::Color_Buffer_Rgba8888 > texture;

        texture = Texture::load_texture(path);


        for (GLint coordinate_index = 0, tx_index = 0; coordinate_index < coordinates.size(); coordinate_index += 3, tx_index += 2)
        {

            int tx_x = (int)( (texture->get_width() - 1) * tx[tx_index]);
            int tx_y = (int)( (texture->get_height() - 1) * tx[tx_index + 1]);

            auto pixel = texture->colors()[texture->offset_at(tx_x, tx_y)];

            float grey_scale = pixel.data.component.r;

            float height = (grey_scale * max_height) / 255;


            coordinates[coordinate_index + 1] = height;

        }


        // COMPROBAMOS LAS NORMALES

        int normalOffset = 0;
        normals.clear();

        for (GLint y = 0; y < vertex_count; ++y)
        {
            for (GLint x = 0; x < vertex_count; ++x)
            {
                GLfloat R = getHeight(x == (vertex_count - 1) ? x : x + 1, y, coordinates);
                GLfloat L = getHeight(x == 0 ? 0 : x - 1, y, coordinates);
                GLfloat B = getHeight(x, y == 0 ? 0 : y - 1, coordinates);
                GLfloat T = getHeight(x, y == (vertex_count - 1) ? y : y + 1, coordinates);

                glm::vec3 normal = glm::normalize(glm::vec3(L - R, T - B, 2));
                normals.push_back(normal.x);// );
                normals.push_back(normal.y);//normal.y );
                normals.push_back(normal.z);// );

            }
        }
    }

    GLfloat Malla::getHeight(int x, int y, const std::vector< GLfloat >& coordinates)
    {
        return coordinates[((y * vertex_count + x) * 3) + 1];
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
                normals.push_back(-1); // y
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
        int vertex_triangles = ((vertex_count - 1) * (vertex_count - 1) * 2);


        int offset = 0;
        for (int i = 0; i < vertex_count - 1; ++i)
        {
            for (int j = 0; j < vertex_count - 1; ++j)
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


    void Malla::render()
    {

        if (textures_factory[materials[0].diffuse_tex_id]->is_ok())
        {
            textures_factory[materials[0].diffuse_tex_id]->bind();
            materials[0].setUniformsValue(scene->getMainCamera()->getShaderProgram());

        }

        glm::mat4 camera_matrix = scene->getMainCamera()->getProjectionMatrix() * scene->getMainCamera()->getTransformation();
        glm::mat4 modelMatrix = transform.getModelViewMatrix();

        glUniformMatrix4fv(scene->getMainCamera()->getProjectionMatrixId(), 1, GL_FALSE, glm::value_ptr(camera_matrix));
        glUniformMatrix4fv(modelMatrixTransformationId, 1, GL_FALSE, glm::value_ptr(modelMatrix));

        // Se selecciona el VAO que contiene los datos del objeto y se dibujan sus elementos:

        glBindVertexArray(vao_id);
        glDrawElements(GL_TRIANGLES, indices.size() * sizeof(GLuint), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }


}
