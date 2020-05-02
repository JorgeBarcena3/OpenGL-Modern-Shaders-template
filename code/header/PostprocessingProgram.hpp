
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef POSTPROCESSINGPROGRAM_HEADER
#define POSTPROCESSINGPROGRAM_HEADER

#include "Shader_Program.hpp"


namespace OpenGLRender3D
{

    using namespace ShaderProgramHelper;
    class Scene;

    class PostprocessingProgram
    {

    public:

        Scene * scene;

    private:

        GLuint effectFrameBuffer_id;

        GLuint effectFramebuffertexture_id;

        GLuint effectRenderBufferObject_id;

        ShaderProgramHelper::Shader_Program shaderProgram;


    public:

        PostprocessingProgram() = delete;

        PostprocessingProgram(Scene& _scene);

        ~PostprocessingProgram();

        void render();

    private:


    };

}

#endif
