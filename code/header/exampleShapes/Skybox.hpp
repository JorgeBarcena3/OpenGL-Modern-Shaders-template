
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on may of 2014                                            *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CUBE_HEADER
#define CUBE_HEADER

#include "BaseModel3D.hpp"

namespace OpenGLRender3D
{

    class Skybox : public BaseModel3D
    {
 
    private:

         ShaderProgramHelper::Shader_Program shaderProgram;

         GLint matrix_id;

    public:

        Skybox(const std::string& path, Scene& scene, OpenGLRender3D::OPACITYMODEL op = OpenGLRender3D::OPACITYMODEL::OPAQUE);
        ~Skybox();

        // Heredado vía BaseModel3D
        virtual void render() override;

        virtual void update(float time) override;

    };

}

#endif
