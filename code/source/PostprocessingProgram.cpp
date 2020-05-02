#include "..\header\PostprocessingProgram.hpp"
#include "..\header\Vertex_Shader.hpp"
#include "..\header\Fragment_Shader.hpp"
#include "..\header\Scene.hpp"
#include "../header/ConfigOptions.hpp"

OpenGLRender3D::PostprocessingProgram::PostprocessingProgram(Scene& _scene) : scene(&_scene)
{

    // Creamos los shader
    shaderProgram.attach(ShaderProgramHelper::Vertex_Shader(ShaderProgramHelper::Shader::Source_Code::from_file(ConfigOptions::ConfigPaths::postprocesing_shader_path + ConfigOptions::ConfigPaths::vertexShader_name)));
    shaderProgram.attach(ShaderProgramHelper::Fragment_Shader(ShaderProgramHelper::Shader::Source_Code::from_file(ConfigOptions::ConfigPaths::postprocesing_shader_path + ConfigOptions::ConfigPaths::fragmentShader_name)));

    shaderProgram.link();

    // Creamos un framebuffer
    glGenFramebuffers(1, &effectFrameBuffer_id);

    // Bindeamos el frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, effectFrameBuffer_id);

    // Si el buffer esta preparado apra utilizarse
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
    {
        // Creamos una textura que renderizara el frame buffer
        {
            glGenTextures(1, &effectFramebuffertexture_id);
            glBindTexture(GL_TEXTURE_2D, effectFramebuffertexture_id);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLint)scene->getWindowSize().x, (GLint)scene->getWindowSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, effectFramebuffertexture_id, 0);
        }

        // Creamos un renderbuffer para utilizarlo a la par
        {
            glGenRenderbuffers(1, &effectRenderBufferObject_id);
            glBindRenderbuffer(GL_RENDERBUFFER, effectRenderBufferObject_id);

            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (GLint)scene->getWindowSize().x, (GLint)scene->getWindowSize().y);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_COMPONENT, GL_RENDERBUFFER, effectRenderBufferObject_id);
        
        }
    }
    else
    {
        std::exception("Error al intentar crear el Frame Buffer Object");
    }



    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

OpenGLRender3D::PostprocessingProgram::~PostprocessingProgram()
{

    glDeleteFramebuffers(1, &effectFrameBuffer_id);
}

void OpenGLRender3D::PostprocessingProgram::render()
{
    shaderProgram.use();

    shaderProgram.disable();
}
