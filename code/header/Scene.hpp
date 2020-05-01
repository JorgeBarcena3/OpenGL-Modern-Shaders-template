
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


namespace OpenGLRender3D
{

    class Camera;
    class Skybox;
    class BaseModel3D;
    class Transform;

    class Scene
    {

    private:

        std::map<std::string, glm::vec3> actionsPool;

        Camera * camera;

        std::map<std::string,  BaseModel3D* > entities;

        std::vector< BaseModel3D* > opaque;
        std::vector< BaseModel3D* > translucid;

        glm::vec2 window_size;

        Skybox * skybox;

        Transform * scene_Node;

    public:

        Scene(int width, int height);

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

        BaseModel3D * getEntity(std::string name)
        {
            return entities[name];
        }

    private:

        void orderEntitiesTransparency();

        void orderEntitiesByDistanceCamera(std::vector< BaseModel3D*>& toOrder);
  

    };

}

#endif
