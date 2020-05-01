
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge Barcena on March of 2020                                  *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef DIRECTIONALLIGHT_HEADER
#define DIRECTIONALLIGHT_HEADER

#include "Light.hpp"

namespace OpenGLRender3D
{

    class DirectionalLight : public Light
    {

    private:

        glm::vec3 direction;

    public:

        DirectionalLight(glm::vec3 _direction) : direction(_direction), Light()
        {

        }


        // Heredado vía Light
        virtual void setUniformVariables(ShaderProgramHelper::Shader_Program& shader) override;

    };

}

#endif
