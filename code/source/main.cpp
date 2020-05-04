
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

    Scene myScene(800, 600, "../../assets/scene/scene.xml");

    window.setTitle(myScene.sceneTitle);
    myScene.getLight("Camera Main Light")->setUpdateFunction(movement);
    //myScene.getEntity("Calavera")->setUpdateFunction(calavera);

    // Se ejecuta el bucle principal:

    bool running = true;

    sf::Clock clock; // starts the clock

    do
    {

        Event event;
        std::vector<std::string> keys;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
            {
                running = false;
                break;
            }

            case Event::Resized:
            {
                Vector2u window_size = window.getSize();

                myScene.resize(window_size.x, window_size.y);

                break;
            }

            case Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                {
                    keys.push_back("W");
                }
                else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                {
                    keys.push_back("S");
                }

                if (event.key.code == sf::Keyboard::Space)
                {
                    keys.push_back("Space");
                }
                else if (event.key.code == sf::Keyboard::LControl)
                {
                    keys.push_back("LControl");
                }

                if (event.key.code == sf::Keyboard::A)
                {
                    keys.push_back("A");
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    keys.push_back("D");
                }
                else if (event.key.code == sf::Keyboard::P)
                {
                    keys.push_back("P");
                }
                else if (event.key.code == sf::Keyboard::Escape)
                {
                    keys.push_back("Esc");
                }
                break;
            }
            }
        }

        if (running)
            running = myScene.manageInput(keys, glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
        myScene.update(clock.getElapsedTime().asSeconds());
        myScene.render();

        window.display();

    } while (running);

    return (EXIT_SUCCESS);
}
