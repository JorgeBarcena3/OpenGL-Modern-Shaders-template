// File: BaseModel3D.hpp
// Author: Jorge Bárcena Lumbreras

// © Copyright (C) 2020  Jorge Bárcena Lumbreras

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
    /**
    * Tipo de opacidad que tiene un modelo de nuestro programa
    */
    const enum class OPACITYMODEL
    {
        OPAQUE = 0,
        TRANSLUCID = 1
    };

    /**
    * Informacion del material de cada modelo
    */
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

        /**
        * Determina si tiene o no textura
        */
        bool hasTexture()
        {
            return (!diffuse_texname.empty());
        }

        /**
        * Obtiene los id de las variables uniformes donde iran la informacion
        */
        void getUniformsId(ShaderProgramHelper::Shader_Program& shaderProgram)
        {
            KaId = shaderProgram.get_uniform_id(ConfigOptions::ConfigPaths::configSettingsMap["shader_myMaterialKa"].c_str());
            KdId = shaderProgram.get_uniform_id(ConfigOptions::ConfigPaths::configSettingsMap["shader_myMaterialKd"].c_str());
            KsId = shaderProgram.get_uniform_id(ConfigOptions::ConfigPaths::configSettingsMap["shader_myMaterialKs"].c_str());
        }

        /**
        * Pasa al shaderprogram la informacion de los materiales
        */
        void setUniformsValue(ShaderProgramHelper::Shader_Program& shaderProgram)
        {
            shaderProgram.set_uniform_value(KaId, Ka);
            shaderProgram.set_uniform_value(KdId, Kd);
            shaderProgram.set_uniform_value(KsId, Ks);
        }

    };

    class Texture;

    /**
    * Clase base de todo modelo que se vaya a renderizar
    */
    class BaseModel3D
    {


    protected:


        /**
        * Indices de los VBO de cada modelo
        */
        enum
        {
            COORDINATES_VBO,
            COLORS_VBO,
            NORMALS_VBO,
            TEXTURE_VBO,
            INDICES_IBO,
            VBO_COUNT
        };

    public:

        Transform transform;                                          ///< Transform del modelo

        Scene* scene;                                                 ///< Escena a la que pertenece


    protected:


        GLuint vbo_ids[VBO_COUNT];                                    ///< Ids de los VBO

        GLuint vao_id;                                                ///< Id del VAO

        std::vector< GLuint > indices;                                ///< Indices del modelo a renderizar

        std::vector<Texture*> textures_factory;                       ///< Texturas utilizadas por el modelo
                                                                      
        std::vector< Material > materials;                            ///< Materiales del modelo
                                                                      
        OpenGLRender3D::OPACITYMODEL opacityModel;                    ///< Tipo de opacidad del modelo
                                                                      
        GLint modelMatrixTransformationId;                            ///< Id de la matriz de transformacion

        std::function<void(BaseModel3D*, float time)> updateFunction; ///< Funcion que se ejecutara en el update

   
    public:

        /**
        * Constructor por defecto
        */
        OpenGLRender3D::BaseModel3D(OPACITYMODEL _model, Scene& _scene)
        {
            opacityModel = _model;
            scene = &_scene;
        }

        /**
        * Destructor por defecto
        */
        ~BaseModel3D();

        /**
        * Funcion virtual de render
        */
        virtual void render() = 0;

        /**
        * Funcion de update por defecto
        */
        virtual void update(float time) 
        {
            if (updateFunction)
                updateFunction(this, time);
        }

        /**
        * Determina la funcion que se ejecutara en el update
        */
        void setUpdateFunction(std::function<void(BaseModel3D*, float time)> UpdateFunction)
        {
            updateFunction = UpdateFunction;
        }

        /**
        * Determina el padre del modelo
        */
        void setParent(Transform* _transform)
        {
            transform.addParent(_transform);
        }

        /**
        * Devuelve la opacidad del modelo
        */
        inline OpenGLRender3D::OPACITYMODEL getOpacityModel()
        {
            return opacityModel;
        }

        /**
        * Determina el material por defecto
        */
        void setDefaultMaterial(std::string path = ConfigOptions::ConfigPaths::configSettingsMap["texture_default_path"]);


    };

}

#endif
