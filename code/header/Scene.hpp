
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SCENE_HEADER
#define SCENE_HEADER

#include <glad/glad.h>
#include <string>
#include <map>
#include <glm/matrix.hpp>
#include <vector>
#include <SFML/Window.hpp>  

namespace OpenGLRender3D
{

    class Camera;
    class Skybox;
    class BaseModel3D;

    class Scene
    {

    private:


        Camera * camera;

        std::vector< BaseModel3D* > shapes;

        glm::vec2 window_size;

        Skybox * skybox;

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

    private:

        std::map<std::string, glm::vec3> actionsPool;

    };

}

#endif
