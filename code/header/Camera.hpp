// File: Camera.hpp
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

#define GLM_FORCE_RADIANS

#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <string>
#include <glm/matrix.hpp>

#include "Shader_Program.hpp"
#include "3DModels/BaseModel3D.hpp"


namespace OpenGLRender3D
{

    using namespace ShaderProgramHelper;

    /**
    * Clase que maneja la camara y su movimiento
    */
    class Camera
    {

        /**
        * Posicion del raton para determinar el movimiento
        */
        struct MousePosition
        {
            float lastx;                ///< Ultima posicion de x (del raton)
            float lasty;                ///< Ultima posicion de y (del raton)
            bool firstPressed = true;   ///< Determina si el click es la primera vez que se produce
        };

        /**
        * Atributos de las transformacions de la camara
        */
        struct CameraTransformAttributes
        {
         
            glm::vec3 front;                ///< Vector front desde la camara
            glm::vec3 up;                   ///< Vector up desde la camara
            glm::vec3 right;                ///< Vector right desde la camara
            glm::vec3 worldUp;              ///< Vector up del mundo desde la camara

            float yaw;                      ///< Angulos de rotacion del yaw ( Y )
            float pitch;                    ///< Angulos de rotacion del pitch ( X )

            float movement_speed;           ///< Velocidad de movimiento de la camara
            float mouse_sensivity;          ///< Sensibilidad de la camara

            /**
            * Contructor del transform de la camara
            */
            CameraTransformAttributes()
            {
                worldUp = glm::vec3(0.f, 1., 0.f);
                yaw = -90.f;
                pitch = 0;
                movement_speed     = 0.15f;
                mouse_sensivity  = 0.2f;
            }
        };

    public:

        Transform transform;                                    ///< Transform de la camara

        CameraTransformAttributes cameraTransformAttributes;    ///< Atributos auxialires de transformacion de la camara

        MousePosition mousePosition;                            ///< Posicion del raton

    private:

        GLint  projection_view_matrix_id;                       ///< Id de la matriz de proyeccion

        GLint  cameraposition_id;                               ///< Id de la posicion de la camara

        glm::mat4 projection_matrix;                            ///< Matriz de proyeccion

        Shader_Program shaderProgram;                           ///< Shaderprogram de la camara

        Scene* scene;                                           ///< Escena a la que pertenece

    public:

        /**
        * Constructor de la camara
        */
        Camera(int width, int height, Scene& scene);

        /**
        * Destructor de la camara
        */
        ~Camera();

        /**
        * Realiza el update de la camara
        */
        void   update(float time);

        /**
        * Renderiza la camara
        */
        void   render();

        /**
        * Cambia el aspect ratio de la camara
        */
        void   resize(int width, int height);

        /**
        * Mueve la camara
        */
        void moveCamera(glm::vec3 movement);
        
        /**
        * Rota la camara
        */
        void rotateCamera(glm::vec2 mousePos);

        /**
        * Devuelve la transformacion de la camara
        */
        const glm::mat4 getTransformation();

        /**
        * Devuelve el id de la matriz de proyeccion
        */
        inline const GLint getProjectionMatrixId()
        {
            return projection_view_matrix_id;
        };

        /**
        * Devuelve la matriz de proyeccion
        */
        inline const glm::mat4 getProjectionMatrix()
        {
            return projection_matrix;
        };

        /**
        * Devuelve el shaderprogram de la camara
        */
        Shader_Program& getShaderProgram()
        {
            return shaderProgram;
        }

        /**
        * Actualiza el transform de la camara
        */
        void updateCameraTransform();



    };

}

#endif
