
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge Barcena on March of 2020                                  *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include <glm/matrix.hpp>
#include "Shader_Program.hpp"


namespace OpenGLRender3D
{

    class Light
    {

    protected:

        glm::vec3 ambientColor;
        glm::vec3 diffuseColor;
        glm::vec3 specularColor;

    public:

        Light(glm::vec3 _ambientColor = glm::vec3(1,1,1), glm::vec3 _diffuseColor = glm::vec3(1, 1, 1), glm::vec3 _specularColor = glm::vec3(1, 1, 1)) :
            ambientColor(_ambientColor), diffuseColor(_diffuseColor), specularColor(_specularColor)
        {
                
        }

        void setAmbientColor(glm::vec3 a)
        {
            ambientColor = a;
        }
        
        void setdiffuseColor(glm::vec3 a)
        {
            diffuseColor = a;
        }
        
        void setSpecularColor(glm::vec3 a)
        {
            specularColor = a;
        }
        
        virtual void setUniformVariables(ShaderProgramHelper::Shader_Program& shader) = 0;


    };

}

#endif
