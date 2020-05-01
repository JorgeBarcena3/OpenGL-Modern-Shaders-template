
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

        GLint directionId;

    public:

        DirectionalLight(glm::vec3 _direction, Scene& scene) : direction(glm::normalize(_direction)), Light(scene)
        {

        }

        void setDirection(glm::vec3 _direction)
        {
            direction = _direction;
        }

        glm::vec3 getDirection()
        {
            return direction;
        }

        // Heredado vía Light
        virtual void setUniformVariables(ShaderProgramHelper::Shader_Program& shader) override;

        // Heredado vía Light
        virtual void getUniformId(ShaderProgramHelper::Shader_Program& shader, std::string lightId) override;

    };

}

#endif
