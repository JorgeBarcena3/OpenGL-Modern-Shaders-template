
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge Barcena on March of 2020                                  *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef POINTLIGHT_HEADER
#define POINTLIGHT_HEADER

#include "Light.hpp"

namespace OpenGLRender3D
{

    class PointLight : public Light
    {

    private:

        glm::vec3 position;

        GLint  positionId;


    public:

        PointLight(glm::vec3 pos) : position(pos), Light()
        {
                
        }
        
        // Heredado v�a Light
        virtual void setUniformVariables(ShaderProgramHelper::Shader_Program& shader) override;

        // Heredado v�a Light
        virtual void getUniformId(ShaderProgramHelper::Shader_Program& shader, std::string lightId) override;

    };

}

#endif
