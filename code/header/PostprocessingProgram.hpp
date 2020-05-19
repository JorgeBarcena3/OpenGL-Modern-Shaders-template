// File: PostProcessingProgram.hpp
// Author: Jorge Bárcena Lumbreras

// © Copyright (C) 2020  Jorge Bárcena Lumbreras

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>


#ifndef POSTPROCESSINGPROGRAM_HEADER
#define POSTPROCESSINGPROGRAM_HEADER

#include "Shader_Program.hpp"


namespace OpenGLRender3D
{

    using namespace ShaderProgramHelper;
    class Scene;

    /**
    * Clase que se encarga de renderizar un shaderprogram de postproceso
    */
    class PostprocessingProgram
    {

    public:

        Scene * scene;                                     ///< Escena a la que pertenece


    private:
        
        GLuint vbo_ids[2];                                 ///< Ids de los VBOs que se usan
        
        GLuint vao_id;                                     ///< Id del VAO del programa de postproceso    

        GLuint frameBuffer_id;                             ///< Id del framebuffer

        GLuint textureColorBuffer_id;                      ///< Id de la textura de la escena

        GLuint depthRenderBuffer_id;                       ///< Id del render buffer

        bool active;                                       ///< Determina si está o no activo el postprocessing program

        ShaderProgramHelper::Shader_Program shaderProgram; ///< Shaderprogram de postprocessing


    public:

        /**
        * Constructor por defecto eliminado
        */
        PostprocessingProgram() = delete;

        /**
        * Constructor del programa
        */
        PostprocessingProgram(Scene& _scene);

        /**
        * Desctructor del programa de postproceso
        */
        ~PostprocessingProgram();

        /**
        * Activamos el framebuffer donde se va a renderizar la escena actual
        */
        void activeCurrentFrameBuffer();

        /**
        * Se aplica el efecto de postproceso
        */
        void render();

        /**
        * Se activa el postproceso
        */
        void setActive(bool a);

        /**
        * Se cambia el estado de activo
        */
        void toggleActive();

        /**
        * Cambia el tamaño de la textura con respecto a la pantalla
        */
        void resize(int width, int height);

    private:

        /**
        * Crea los VAO
        */
        void createScreenCoordinatesVAO();

        /**
        * Crea el framebuffer para mas tarde aplicar el postproceso
        */
        void createEffectFrameBuffer();

    };

}

#endif
