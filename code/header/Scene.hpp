
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

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include <string>
#include <glm/matrix.hpp>
#include <vector>

namespace OpenGLRender3D
{

    class Camera;
    class BaseModel3D;

    class Scene
    {

    private:


        Camera* camera;
        std::vector< BaseModel3D* > shapes;

    public:

        Scene(int width, int height);

        void   update(float time);
        void   render();

        Camera* getMainCamera();

    };

}

#endif
