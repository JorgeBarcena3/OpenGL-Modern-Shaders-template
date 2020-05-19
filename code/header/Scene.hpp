// File: Scene.hpp
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

#ifndef SCENE_HEADER
#define SCENE_HEADER


#include <string>
#include <glm/matrix.hpp>
#include <vector>
#include <map>
#include "PostprocessingProgram.hpp"


namespace OpenGLRender3D
{

    class Camera;
    class Skybox;
    class BaseModel3D;
    class Transform;
    class DirectionalLight;
    class PointLight;
    class Light;

    /**
    * Clase que se encarga de crear y renderizar una escena
    */
    class Scene
    {

        friend class XMLParser;

    public:

        std::string sceneTitle;                                ///< Titulo de la escena

    private:

        std::map<std::string, glm::vec3> actionsPool;           ///< Acciones a realizar en la escena
         
        Camera* camera;                                         ///< Camara principal

        std::map<std::string, BaseModel3D* > entities;          ///< Entidades de la escena

        std::vector< BaseModel3D* > opaque;                     ///< Entidades opacas

        std::vector< BaseModel3D* > translucid;                 ///< Entidades translucidas

        glm::vec2 window_size;                                  ///< Tamaño de la pantalla

        PostprocessingProgram* postpoProgram;                   ///< Programa de postproceso

        Skybox* skybox;                                         ///< Skybox de la escena

        std::map<std::string, Light* > lights;                  ///< Luces de la escena

        Transform* scene_Node;                                  ///< Nodo principal de la escena

    public:

        /**
        * Constructor de la escena
        */
        Scene(int width, int height, std::string path);

        /**
        * Destructor de la escena
        */
        ~Scene();

        /**
        * Update de la escena
        */
        void   update(float time);

        /**
        * Render de la escena
        */
        void   render();

        /**
        * Añade una entidad a la escena
        */
        void addEntity(std::string name, BaseModel3D* entity);

        /**
        * Elimina una entidad a la escena
        */
        void removeEntity(std::string name);

        /**
        * Añade una luz a la escena
        */
        void addLight(std::string name, Light* entity);

        /**
        * Elimina una luz a la escena
        */
        void removeLight(std::string name);

        /**
        * Cambia el aspect ratio en funcion de la pantalla de la escena
        */
        void Scene::resize(int width, int height);

        /**
        * Procesa el input del usuario 
        */
        bool Scene::manageInput(std::vector<std::string> keys, glm::vec2 mousePosition, bool mousePressed);

        /**
        * Devuelve la camara principal
        */
        Camera* getMainCamera();

        /**
        * Devuelve el tamaño de la escena
        */
        inline glm::vec2 getWindowSize()
        {
            return window_size;
        }

        /**
        * Cambia el tamaño de la pantalla
        */
        inline void setWindowSize(int width, int height)
        {

            window_size = glm::vec2(width, height);
        }

        /**
        * Devuelve una entidad con ese nombre asignado
        */
        inline BaseModel3D* getEntity(std::string name)
        {
            return entities[name];
        }

        /**
        * Devuelve una luz con un nombre asignado
        */
        inline Light* getLight(std::string name)
        {
            return lights[name];
        }

    private:

        /**
        * En caso de que existan acciones pendientes las realiza
        */
        void cleanActionsPool();

        /**
        * Ordan las entidades por transparencia
        */
        void orderEntitiesTransparency();

        /**
        * Ordena las entidades por distancia a la camara
        */
        void orderEntitiesByDistanceCamera(std::vector< BaseModel3D*>& toOrder);


    };

}

#endif
