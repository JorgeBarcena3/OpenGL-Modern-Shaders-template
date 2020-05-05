#include "../header/SFMLApplication.hpp"


#include <SFML/Window.hpp>
#include <time.h>

#include "../header/Scene.hpp"
#include "../header/PointLight.hpp"
#include "../header/3DModels/BaseModel3D.hpp"

using namespace sf;
using namespace OpenGLRender3D;

void movement(Light* me, float time)
{
    PointLight* point = (PointLight*)me;

    point->setPosition(point->getScene()->getMainCamera()->transform.getPosition());
}

void calavera(OpenGLRender3D::BaseModel3D* me, float time)
{

    me->transform.setRotation(me->transform.getRotation() + glm::vec3(0, 0, 1));

}

OpenGLRender3D::SFMLApplication::SFMLApplication(std::string path)
{
    srand((unsigned int)time(NULL));

    window = new Window(VideoMode(800, 600), "OpenGL Rendering - Jorge Barcena Lumbreras", Style::Default, ContextSettings(32));

    window->setVerticalSyncEnabled(true);

    if (!gladLoadGL())
        throw std::exception("No se ha podido cargar el contexto de OpenGL");

    myScene = new Scene(800, 600, path);

    window->setTitle(myScene->sceneTitle);

}

OpenGLRender3D::SFMLApplication::~SFMLApplication()
{
    delete window;
    delete myScene;
}

void OpenGLRender3D::SFMLApplication::start()
{

    // Se ejecuta el bucle principal:

    bool running = true;

    do
    {
        Event event;
        std::vector<std::string> keys;

        while (window->pollEvent(event))
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
                Vector2u window_size = window->getSize();

                myScene->resize(window_size.x, window_size.y);

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
            running = myScene->manageInput(keys, glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
        myScene->update(0);
        myScene->render();

        window->display();

    } while (running);

}


