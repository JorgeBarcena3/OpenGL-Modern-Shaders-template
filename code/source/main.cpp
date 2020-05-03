
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

void calavera(BaseModel3D* me, float time)
{
    static float angle = 0;

    angle = 1;

    me->transform.setRotation(me->transform.getRotation() + glm::vec3(0, 0, 1));

}


int main()
{

    srand((unsigned int)time(NULL));

    Window window(VideoMode(800, 600), "OpenGL Rendering - Jorge Barcena Lumbreras", Style::Default, ContextSettings(32));

    window.setVerticalSyncEnabled(true);

    if (!gladLoadGL())
        throw std::exception("No se ha podido cargar el contexto de OpenGL");

    Scene myScene(800, 600, "../../assets/scene/scene.xml", window);

    myScene.getLight("Camera Main Light")->setUpdateFunction(movement);
    myScene.getEntity("Calavera")->setUpdateFunction(calavera);

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
