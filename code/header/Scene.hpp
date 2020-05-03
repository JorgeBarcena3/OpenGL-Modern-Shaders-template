
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#define GLM_FORCE_RADIANS

#ifndef SCENE_HEADER
#define SCENE_HEADER


#include <SFML/Window.hpp>  
#include <glad/glad.h>
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

    class Scene
    {

    private:

        std::map<std::string, glm::vec3> actionsPool;

        Camera* camera;

        std::map<std::string, BaseModel3D* > entities;

        std::vector< BaseModel3D* > opaque;

        std::vector< BaseModel3D* > translucid;

        glm::vec2 window_size;

        PostprocessingProgram* postpoProgram;

        Skybox* skybox;

        std::map<std::string, Light* > lights;

        Transform* scene_Node;

        sf::Window* window;

        /*
        * La clase XMLParser puede acceder a las variables privadas de la escena
        */
        friend class XMLParser;

    public:

        Scene(int width, int height, std::string path, sf::Window& window);

        ~Scene();

        void   update(float time);
        void   render();
        void   cleanActionsPool();

        bool manageInput(sf::Window& wd);

        Camera* getMainCamera();

        inline glm::vec2 getWindowSize()
        {
            return window_size;
        }

        void setWindowSize(int width, int height)
        {

            window_size = glm::vec2(width, height);
        }

        BaseModel3D* getEntity(std::string name)
        {
            return entities[name];
        }

        Light* getLight(std::string name)
        {
            return lights[name];
        }

    private:

        void configureEntities();

        void configureLights();

        void addEntity(std::string name, BaseModel3D* entity);

        void addLight(std::string name, Light* entity);

        void orderEntitiesTransparency();

        void orderEntitiesByDistanceCamera(std::vector< BaseModel3D*>& toOrder);


    };

}

#endif
