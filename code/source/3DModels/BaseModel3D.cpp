#include "..\..\header\3DModels\BaseModel3D.hpp"
#include "..\..\header\Texture2D.hpp"
#include "..\..\header\Scene.hpp"
#include "..\..\header\Camera.hpp"

OpenGLRender3D::BaseModel3D::~BaseModel3D()
{
    for (auto tex : textures_factory)
    {
        delete tex;
    }
}

void OpenGLRender3D::BaseModel3D::setDefaultMaterial(std::string path)
{
    Material mat;

    mat.Ka = glm::vec3(0.5f);
    mat.Kd = glm::vec3(0.5f);
    mat.Ks = glm::vec3(0);

    mat.diffuse_texname = "default";
    textures_factory.push_back(new Texture2D(path));
    mat.diffuse_tex_id = textures_factory.size() - 1;

   /* mat.specular_texname = "default";
    textures_factory.push_back(new Texture2D(path));
    mat.specular_tex_id = textures_factory.size() - 1;*/

    mat.getUniformsId(scene->getMainCamera()->getShaderProgram());

    materials.push_back(mat);
}
