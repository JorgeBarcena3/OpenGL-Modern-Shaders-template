
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "../header/Scene.hpp"
#include <iostream>
#include <cassert>
#include "../header/exampleShapes/Cylinder.hpp"
#include "../header/exampleShapes/Malla.hpp"
#include "../header/Camera.hpp"


namespace OpenGLRender3D
{

    using namespace std;

    Scene::Scene(int width, int height)
    {
        camera = new OpenGLRender3D::Camera(width, height);

        shapes.push_back(new OpenGLRender3D::Malla(5, 5, 32, *this, "../../assets/height_map/Volcan.tga"));

    }

    void Scene::update(float time)
    {

        camera->update(time);

        for (auto shape : shapes)
        {
            shape->update();
        }
    }

    void Scene::render()
    {

        camera->render();

        //Se renderizan las shapes
        for (auto shape : shapes)
        {
            shape->render();
        }

    }

    Camera* Scene::getMainCamera()
    {
        return camera;
    };


}
