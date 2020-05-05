
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef BASESHAPES_HEADER
#define BASESHAPES_HEADER

#include <memory>
#include <vector>
#include <functional>
#include <cmath>

#include "../Scene.hpp"
#include "../Transform.hpp"
#include "../ConfigOptions.hpp"

namespace OpenGLRender3D
{
    const enum class OPACITYMODEL
    {
        OPAQUE = 0,
        TRANSLUCID = 1
    };

    struct Material
    {

        glm::vec3 Ka;
        glm::vec3 Kd;
        glm::vec3 Ks;

        GLint KaId;
        GLint KdId;
        GLint KsId;

        std::string diffuse_texname;
        int diffuse_tex_id;

        bool hasTexture()
        {
            return (!diffuse_texname.empty());
        }

        void getUniformsId(ShaderProgramHelper::Shader_Program& shaderProgram)
        {
            KaId = shaderProgram.get_uniform_id(ConfigOptions::ConfigPaths::configSettingsMap["shader_myMaterialKa"].c_str());
            KdId = shaderProgram.get_uniform_id(ConfigOptions::ConfigPaths::configSettingsMap["shader_myMaterialKd"].c_str());
            KsId = shaderProgram.get_uniform_id(ConfigOptions::ConfigPaths::configSettingsMap["shader_myMaterialKs"].c_str());
        }

        void setUniformsValue(ShaderProgramHelper::Shader_Program& shaderProgram)
        {
            shaderProgram.set_uniform_value(KaId, Ka);
            shaderProgram.set_uniform_value(KdId, Kd);
            shaderProgram.set_uniform_value(KsId, Ks);
        }

    };

    class Texture;

    class BaseModel3D
    {


    protected:


        // Índices para indexar el array vbo_ids:

        enum
        {
            COORDINATES_VBO,
            COLORS_VBO,
            NORMALS_VBO,
            TEXTURE_VBO,
            INDICES_IBO,
            VBO_COUNT
        };




    protected:

        GLuint vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan

        GLuint vao_id;                  // Id del VAO del cubo

        std::vector< GLuint > indices;

        std::vector<Texture*> textures_factory;

        std::vector< Material > materials;

        OpenGLRender3D::OPACITYMODEL opacityModel;

        GLint modelMatrixTransformationId;

        /*
       * Funcion que se ejecutara en el update
       */
        std::function<void(BaseModel3D*, float time)> updateFunction;



    public:

        OpenGLRender3D::BaseModel3D(OPACITYMODEL _model, Scene& _scene)
        {
            opacityModel = _model;
            scene = &_scene;
        }

        ~BaseModel3D();

        Transform transform;

        Scene* scene;

        virtual void render() = 0;

        virtual void update(float time) 
        {
            if (updateFunction)
                updateFunction(this, time);
        }

        /*
        * Determina cual será la funcion de update del modelo
        */
        void setUpdateFunction(std::function<void(BaseModel3D*, float time)> UpdateFunction)
        {
            updateFunction = UpdateFunction;
        }

        void setParent(Transform* _transform)
        {
            transform.addParent(_transform);
        }

        OpenGLRender3D::OPACITYMODEL getOpacityModel()
        {
            return opacityModel;
        }

        void setDefaultMaterial(std::string path = ConfigOptions::ConfigPaths::configSettingsMap["texture_default_path"]);


    };

}

#endif
