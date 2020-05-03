
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
    public:

        static GLint light_id;


    private:

        glm::vec3 position;

        GLint  positionId;


    public:

        PointLight(glm::vec3 pos, Scene& scene) : position(pos), Light(scene)
        {
                
        }

        void setPosition(glm::vec3 _direction)
        {
            position = _direction;
        }

        glm::vec3 getPosition()
        {
            return position;
        }
        
        // Heredado vía Light
        virtual void setUniformVariables(ShaderProgramHelper::Shader_Program& shader) override;

        // Heredado vía Light
        virtual void getUniformId(ShaderProgramHelper::Shader_Program& shader, std::string lightId) override;

    };

}

#endif
