
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>

#include "../header/Scene.hpp"
#include "../header/PointLight.hpp"



using namespace sf;
using namespace OpenGLRender3D;

void movement(Light* me, float time)
{
    PointLight* point = (PointLight*)me;

    point->setPosition(point->getScene()->getMainCamera()->transform.getPosition());
}


int main()
{

    srand((unsigned int)time(NULL));

    Window window(VideoMode(800, 600), "OpenGL Modern + Shaders + textures", Style::Default, ContextSettings(32));

    window.setVerticalSyncEnabled(true);

    if (!gladLoadGL())
        throw std::exception("No se ha podido cargar el contexto de OpenGL");

    Scene myScene(800, 600);

    myScene.getLight("Sun")->setUpdateFunction(movement);
    myScene.getEntity("Calavera")->transform.setRotation(glm::vec3(-90, 0, 0));

    // Se ejecuta el bucle principal:

    bool running = true;

    sf::Clock clock; // starts the clock

    do
    {

        running = myScene.manageInput(window);
        myScene.update(clock.getElapsedTime().asSeconds());
        myScene.render();

        window.display();

    } while (running);

    return (EXIT_SUCCESS);
}
