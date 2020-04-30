
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

#include <SFML/OpenGL.hpp>
#include "BaseModel3D.hpp"

namespace OpenGLRender3D
{

    class Skybox : public BaseModel3D
    {
 
    private:

         shaderToolkit::Shader_Program shaderProgram;

    public:

        Skybox(const std::string& path, Scene& scene);
        ~Skybox();

        // Heredado vía BaseModel3D
        virtual void render() override;

        virtual void update() override;

    };

}

#endif
