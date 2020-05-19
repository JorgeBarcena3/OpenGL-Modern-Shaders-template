// File: Light.hpp
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
// along with this program.  If not, see <https://www.gnu.org/licenses/>

#define GLM_FORCE_RADIANS

#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include <glm/matrix.hpp>
#include <functional>

#include "Shader_Program.hpp"
#include "Scene.hpp"
#include "Camera.hpp"


namespace OpenGLRender3D
{

    /**
    * Clase base de la luz
    */
    class Light
    {

    protected:

        int eneabled;                                           ///< Determina si esta activada o no

        glm::vec3 ambient;                                      ///< Color ambiente

        glm::vec3 diffuse;                                      ///< Color difuso

        glm::vec3 specular;                                     ///< Color especular

        glm::vec3 color;                                        ///< Color

        glm::vec3 intensity;                                    ///< Intensidad de la luz

        GLint ambientId ;                                       ///< Id del color ambiente

        GLint difusseId ;                                       ///< Id del color difuso

        GLint specularId;                                       ///< Id del color especular

        GLint intensityId;                                      ///< Id de la intensidad

        GLint eneabledId;                                       ///< Id de activada o no

        GLint colorId;                                          ///< Id del color
                                                                
        Scene* scene;                                           ///< Escena a la que pertenece

        std::function<void(Light*, float time)> updateFunction; ///< Funcion que se ejecutará en el update

    public:

        /**
        * Constructor por defecto de la luz
        */
        Light(Scene& _scene, glm::vec3 _color = glm::vec3(1,0,0), glm::vec3 _ambientColor = glm::vec3(0,0,0), glm::vec3 _intensity = glm::vec3(1,1,1), glm::vec3 _diffuseColor = glm::vec3(1, 1, 1), glm::vec3 _specularColor = glm::vec3(0,0,0)) :
            scene(&_scene),ambient(_ambientColor), diffuse(_diffuseColor), specular(_specularColor), eneabled(0), color(_color), intensity(_intensity)
        {
                
        }

        /**
        * Determina el color ambiente
        */
        void setAmbientColor(glm::vec3 a)
        {
            ambient = a;
        }
        
        /**
        * Determina el color difuso
        */
        void setdiffuseColor(glm::vec3 a)
        {
            diffuse = a;
        }
        
        /**
        * Determina el color especular
        */
        void setSpecularColor(glm::vec3 a)
        {
            specular = a;
        }
        
        /**
        * Determina el color de la luz
        */
        void setColor(glm::vec3 a)
        {
            color = a;
        }

        /**
        * Determina si la luz esta activa
        */
        void setEneabled(int isEneabled)
        {
            eneabled = isEneabled;
        }
        
        /**
        * Determina la intensidad de la luz
        */
        void setIntensity(glm::vec3 _intensity)
        {
            intensity = _intensity;
        }
        
        /**
        * Actualiza los datos de la luz 
        */
        void refreshLightData(ShaderProgramHelper::Shader_Program& shader)
        {
            setUniformVariables(shader);
        }

        /**
        * Determina la escena donde está la luz
        */
        inline Scene* getScene()
        {
            return scene;
        }

        /**
        * Setea todas las variables uniformes
        */
        virtual void setUniformVariables(ShaderProgramHelper::Shader_Program& shader) = 0;

        /**
        * Obtiene los id de la variable de las luces
        */
        virtual void getUniformId(ShaderProgramHelper::Shader_Program& shader, std::string lightId) = 0;

        /**
        * Determina cual será la funcion de update de la luz
        */
        void setUpdateFunction(std::function<void(Light*, float time)> UpdateFunction);


        /**
        * Ejecuta la funcion update de la luz
        */
        void update(float time)
        {
            if (updateFunction)
            {

                updateFunction(this, time);
                setUniformVariables(scene->getMainCamera()->getShaderProgram());

            }
        }


    };

}

#endif
