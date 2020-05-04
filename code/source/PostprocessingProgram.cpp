#include "..\header\PostprocessingProgram.hpp"
#include "..\header\Vertex_Shader.hpp"
#include "..\header\Fragment_Shader.hpp"
#include "..\header\Scene.hpp"
#include "../header/ConfigOptions.hpp"

GLfloat tx_positions[] = {
    // texCoords
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f
};

GLfloat screenVertex[] = {
    // positions  
    -1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f
};

OpenGLRender3D::PostprocessingProgram::PostprocessingProgram(Scene& _scene) : scene(&_scene)
{

    // Creamos los shader
    shaderProgram.attach(ShaderProgramHelper::Vertex_Shader(ShaderProgramHelper::Shader::Source_Code::from_file(ConfigOptions::ConfigPaths::configSettingsMap["postprocesing_shader_path"] + ConfigOptions::ConfigPaths::configSettingsMap["vertexShader_name"])));
    shaderProgram.attach(ShaderProgramHelper::Fragment_Shader(ShaderProgramHelper::Shader::Source_Code::from_file(ConfigOptions::ConfigPaths::configSettingsMap["postprocesing_shader_path"] + ConfigOptions::ConfigPaths::configSettingsMap["fragmentShader_name"])));

    shaderProgram.link();

    createEffectFrameBuffer();

    createScreenCoordinatesVAO();

    active = true;


}

OpenGLRender3D::PostprocessingProgram::~PostprocessingProgram()
{
    glDeleteTextures(1, &textureColorBuffer_id);
    glDeleteVertexArrays(1, &vao_id);
    glDeleteBuffers(2, vbo_ids);
    glDeleteRenderbuffers(1, &depthRenderBuffer_id);
    glDeleteFramebuffers(1, &frameBuffer_id);
}

void OpenGLRender3D::PostprocessingProgram::activeCurrentFrameBuffer()
{
    if (active)
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_id);

}

void OpenGLRender3D::PostprocessingProgram::render()
{

    if (active)
    {
        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);

        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();

        glBindVertexArray(vao_id);
        glBindTexture(GL_TEXTURE_2D, textureColorBuffer_id);	// use the color attachment texture as the texture of the quad plane
        glDrawArrays(GL_TRIANGLES, 0, 6);

        shaderProgram.disable();
    }
}

void OpenGLRender3D::PostprocessingProgram::setActive(bool a)
{
    active = a;
}

void OpenGLRender3D::PostprocessingProgram::toggleActive()
{
    active = !active;
}

void OpenGLRender3D::PostprocessingProgram::resize(int width, int height)
{

    // Bindeamos el frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_id);

    glDeleteTextures(1, &textureColorBuffer_id);

    // Creamos una textura que renderizara el frame buffer
    {
        glGenTextures(1, &textureColorBuffer_id);
        glBindTexture(GL_TEXTURE_2D, textureColorBuffer_id);

        glTexImage2D
        (
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            (GLint)width,
            (GLint)height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            NULL
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer_id, 0);

    }

    // Creamos un renderbuffer de la Z para utilizarlo a la par
    {
        glDeleteRenderbuffers(1, &depthRenderBuffer_id);

        glGenRenderbuffers(1, &depthRenderBuffer_id);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer_id);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (GLint)width, (GLint)height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer_id);

    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

void OpenGLRender3D::PostprocessingProgram::createScreenCoordinatesVAO()
{
    // screen quad VAO
    glGenBuffers(2, vbo_ids);
    glGenVertexArrays(1, &vao_id);

    glBindVertexArray(vao_id);

    // Coordenadas de la pantalla
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[0]);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), screenVertex, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Coordenadas de uv
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[1]);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), tx_positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);

}

void OpenGLRender3D::PostprocessingProgram::createEffectFrameBuffer()
{
    // Creamos un framebuffer
    glGenFramebuffers(1, &frameBuffer_id);

    // Bindeamos el frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_id);


    // Creamos una textura que renderizara el frame buffer
    {
        glGenTextures(1, &textureColorBuffer_id);
        glBindTexture(GL_TEXTURE_2D, textureColorBuffer_id);

        glTexImage2D
        (
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            (GLint)scene->getWindowSize().x,
            (GLint)scene->getWindowSize().y,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            NULL
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer_id, 0);

    }

    // Creamos un renderbuffer de la Z para utilizarlo a la par
    {
        glGenRenderbuffers(1, &depthRenderBuffer_id);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer_id);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (GLint)scene->getWindowSize().x, (GLint)scene->getWindowSize().y);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer_id);

    }

    // Se configura el framebuffer:
    {
        //glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureColorBuffer_id, 0);

        GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
        glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
    }


    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        throw std::exception("Error al intentar crear el Frame Buffer Object del postprocesado");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

