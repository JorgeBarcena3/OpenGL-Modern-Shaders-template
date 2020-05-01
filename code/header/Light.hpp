
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

#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include <glm/matrix.hpp>
#include <functional>

#include "Shader_Program.hpp"
#include "Scene.hpp"
#include "Camera.hpp"


namespace OpenGLRender3D
{

    class Light
    {

    protected:

        int eneabled;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 color;
        glm::vec3 intensity;

        GLint ambientId ;
        GLint difusseId ;
        GLint specularId;
        GLint intensityId;
        GLint eneabledId;
        GLint colorId;

        Scene* scene;

        /*
       * Funcion que se ejecutara en el update
       */
        std::function<void(Light*, float time)> updateFunction;

    public:

        Light(Scene& _scene, glm::vec3 _color = glm::vec3(1,0,0), glm::vec3 _ambientColor = glm::vec3(0,0,0), glm::vec3 _intensity = glm::vec3(1,1,1), glm::vec3 _diffuseColor = glm::vec3(1, 1, 1), glm::vec3 _specularColor = glm::vec3(0,0,0)) :
            scene(&_scene),ambient(_ambientColor), diffuse(_diffuseColor), specular(_specularColor), eneabled(0), color(_color), intensity(_intensity)
        {
                
        }

        void setAmbientColor(glm::vec3 a)
        {
            ambient = a;
        }
        
        void setdiffuseColor(glm::vec3 a)
        {
            diffuse = a;
        }
        
        void setSpecularColor(glm::vec3 a)
        {
            specular = a;
        }
        
        void setColor(glm::vec3 a)
        {
            color = a;
        }

        void setEneabled(int isEneabled)
        {
            eneabled = isEneabled;
        }
        
        void setIntensity(glm::vec3 _intensity)
        {
            intensity = _intensity;
        }
        
        void refreshLightData(ShaderProgramHelper::Shader_Program& shader)
        {
            setUniformVariables(shader);
        }

        virtual void setUniformVariables(ShaderProgramHelper::Shader_Program& shader) = 0;

        virtual void getUniformId(ShaderProgramHelper::Shader_Program& shader, std::string lightId) = 0;

        /*
       * Determina cual será la funcion de update del modelo
       */
        void setUpdateFunction(std::function<void(Light*, float time)> UpdateFunction);

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
