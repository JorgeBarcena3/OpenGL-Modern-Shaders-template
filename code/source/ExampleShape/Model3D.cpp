#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"


#include "..\..\header\exampleShapes\Model3D.hpp"
#include "..\..\header\exampleShapes\Mesh.hpp"
#include "..\..\header\Texture2D.hpp"
#include "..\..\header\Camera.hpp"

OpenGLRender3D::Model3D::Model3D(Scene& _scene, OpenGLRender3D::OPACITYMODEL op, const char* path) :
    BaseModel3D(op, _scene)
{

    loadObj(path); 

}

OpenGLRender3D::Model3D::~Model3D()
{
    // Se liberan los VBOs y el VAO usados:

    glDeleteVertexArrays(1, &vao_id);
    glDeleteBuffers(VBO_COUNT, vbo_ids);
}

void OpenGLRender3D::Model3D::setUpdateFunction(std::function<void(Model3D*)> _updateFunction)
{
    updateFunction = _updateFunction;
}

void OpenGLRender3D::Model3D::loadObj(const char* path)
{

    std::vector< GLfloat > coordinates;
    std::vector< GLfloat > normals;
    std::vector< GLfloat > tx;


    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materals;

    std::string warn;
    std::string err;

    std::string mtlPath = path;

    if (mtlPath.find_last_of("/\\") != std::string::npos)
        mtlPath = mtlPath.substr(0, mtlPath.find_last_of("/\\"));
    else
        mtlPath = ".";


    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materals, &warn, &err, path, mtlPath.c_str());


    if (ret) //Colocamos los datos necesarios
    {
        if (attrib.normals.size() == 0) throw "Este modelo no tiene normales";
        if (attrib.vertices.size() == 0) throw "Este modelo no tiene vertices";
        if (attrib.texcoords.size() == 0) throw "Este modelo no tiene coordenadas de textura";

        if (materals.size() == 0)
        {
            Material mat;

            mat.Ka = glm::vec3(1, 1, 1);
            mat.Kd = glm::vec3(1, 1, 1);
            mat.Ks = glm::vec3(1, 1, 1);

            mat.diffuse_texname = "default";
            textures_factory.push_back(new Texture2D("../../assets/default/texture.tga"));
            mat.diffuse_tex_id = textures_factory.size() - 1;

            mat.specular_texname = "default";
            textures_factory.push_back(new Texture2D("../../assets/default/texture.tga"));
            mat.specular_tex_id = textures_factory.size() - 1;

            materials.push_back(mat);
        }
        else
        {
            //Añadimos los materiales si los hay
            for (size_t m = 0; m < materals.size(); m++)
            {

                Material mat;

                mat.Ka = glm::vec3(materals[m].ambient[0], materals[m].ambient[1], materals[m].ambient[2]);
                mat.Kd = glm::vec3(materals[m].diffuse[0], materals[m].diffuse[1], materals[m].diffuse[2]);
                mat.Ks = glm::vec3(materals[m].specular[0], materals[m].specular[1], materals[m].specular[2]);
       

                mat.diffuse_texname = materals[m].diffuse_texname;
                mat.specular_texname = materals[m].specular_texname;

                if (mat.hasTexture())
                {
                    if (!mat.diffuse_texname.empty())
                    {
                        textures_factory.push_back(new Texture2D(mtlPath + "/" + mat.diffuse_texname));
                        mat.diffuse_tex_id = textures_factory.size() - 1;
                    }


                    if (!mat.specular_texname.empty())
                    {
                        textures_factory.push_back(new Texture2D(mtlPath + "/" + mat.specular_texname));
                        mat.specular_tex_id = textures_factory.size() - 1;
                    }
                }
                else
                {
                    mat.diffuse_texname = "default";
                    textures_factory.push_back(new Texture2D("../../assets/default/texture.tga"));
                    mat.diffuse_tex_id = textures_factory.size() - 1;

                    mat.specular_texname = "default";
                    textures_factory.push_back(new Texture2D("../../assets/default/texture.tga"));
                    mat.specular_tex_id = textures_factory.size() - 1;
                }

                materials.push_back(mat);

            }
        }

        // Offset de los indices de los triangulos
        int indexOffset = 0;

        // En cada mesh añadimos los indices de sus vertices
        // Tambien guardamos los triangulos que forman sus caras
        for (size_t s = 0; s < shapes.size(); s++)
        {

            int indice_count = shapes[s].mesh.indices.size();
            std::vector< GLuint > mesh_indices;
            GLuint mesh_material_index = 0;

            for (int index = 0, matIndex = 0; index < indice_count; index++)
            {
                int vertexIndex = shapes[s].mesh.indices[index].vertex_index;
                int normalIndex = shapes[s].mesh.indices[index].normal_index;
                int texture_index = shapes[s].mesh.indices[index].texcoord_index;

                if (index % 3 == 0 && index != 0)
                    matIndex++;

                int materialIndex = shapes[s].mesh.material_ids[matIndex] == -1 ? 0 : shapes[s].mesh.material_ids[matIndex];

                /********
                 VERTICES
                *********/
                coordinates.push_back(attrib.vertices[3 * vertexIndex + 0]);
                coordinates.push_back(attrib.vertices[3 * vertexIndex + 1]);
                coordinates.push_back(attrib.vertices[3 * vertexIndex + 2]);

                /********
                 NORMALES
                *********/
                normals.push_back(attrib.normals[3 * normalIndex + 0]);
                normals.push_back(attrib.normals[3 * normalIndex + 1]);
                normals.push_back(attrib.normals[3 * normalIndex + 2]);

                /********
                 TEXTURE
                *********/
                tx.push_back(attrib.texcoords[2 * texture_index + 0]);
                tx.push_back(1.0f - attrib.texcoords[2 * texture_index + 1]);

                /********
                 MATERIALS
                *********/
                mesh_material_index = (mesh_material_index);


                mesh_indices.push_back((GLuint)(indexOffset + index));
            }

            meshes.push_back(new Mesh(mesh_indices, *this, mesh_material_index));
            indices.insert(std::end(indices), std::begin(mesh_indices), std::end(mesh_indices));
            indexOffset += indice_count;

        }

    }
    else
    {
        return;
    }

    // Se generan índices para los VBOs del cubo:

    glGenBuffers(VBO_COUNT, vbo_ids);
    glGenVertexArrays(1, &vao_id);

    // Se activa el VAO del cubo para configurarlo:

    glBindVertexArray(vao_id);


    /**********************
    ** DATOS DE VERTICES **
    ***********************/

    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
    glBufferData(GL_ARRAY_BUFFER, coordinates.size() * sizeof(GLfloat), &coordinates[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


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


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_IBO]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);


}

void OpenGLRender3D::Model3D::update()
{
    static float angle = 0;
    angle -= 1;

    transform.setRotation(glm::vec3(angle, 0, 0));

    if (updateFunction)
        updateFunction(this);
}

void OpenGLRender3D::Model3D::render()
{
    for each (auto m in meshes)
    {
        m->render();
    }
}

