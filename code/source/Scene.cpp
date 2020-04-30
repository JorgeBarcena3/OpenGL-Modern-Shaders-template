
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
#include "../header/exampleShapes/Skybox.hpp"
#include <SFML/Window/Mouse.hpp>


namespace OpenGLRender3D
{

    using namespace std;

    Scene::Scene(int width, int height)
    {
        camera = new OpenGLRender3D::Camera(width, height, *this);

        skybox = new OpenGLRender3D::Skybox("../../assets/skybox/sky-cube-map-", *this);

        window_size = glm::vec2(width, height);

        shapes.push_back(new OpenGLRender3D::Malla(25, 25, 256, *this, "../../assets/height_map/Volcan.tga"));

    }

    void Scene::update(float time)
    {
        cleanActionsPool();

        camera->update(time);
        skybox->update();


        for (auto shape : shapes)
        {
            shape->update();
        }
    }

    void Scene::render()
    {


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.5f, 0.5f, 0.5f, 1.f);

        skybox->render();

        camera->render();

        //Se renderizan las shapes
        for (auto shape : shapes)
        {
            shape->render();
        }

    }

    void Scene::cleanActionsPool()
    {
        for each (auto action in actionsPool)
        {
            if (action.first == "Mover Camara")
            {
                camera->moveCamera(action.second);
            }
        }


        actionsPool.clear();
    }

    bool Scene::manageInput(sf::Window& window)
    {
        sf::Event event;

        window.setTitle(sf::String(std::to_string(sf::Mouse::getPosition(window).x)));

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                return false;
                break;
            }

            case sf::Event::Resized:
            {
                sf::Vector2u window_size = window.getSize();

                getMainCamera()->resize(window_size.x, window_size.y);

                break;
            }

            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                {
                    actionsPool.emplace("Mover Camara", -camera->transform.getFordwardVector());
                }
                else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                {
                    actionsPool.emplace("Mover Camara", camera->transform.getFordwardVector());
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    actionsPool.emplace("Mover Camara", glm::vec4(0, 1.0f, 0, 0));
                }
                else if (event.key.code == sf::Keyboard::LControl)
                {
                    actionsPool.emplace("Mover Camara", glm::vec4(0, -1.0f, 0, 0));
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    actionsPool.emplace("Mover Camara", glm::vec4(-1.f, 0.f, 0, 0));
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    actionsPool.emplace("Mover Camara", glm::vec4(+1.f, 0, 0, 0));
                }
            }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            glm::vec2 pos_glm = glm::vec2({ pos.x, pos.y });
            camera->rotateCamera(pos_glm);
        }


        return true;
    }

    Camera* Scene::getMainCamera()
    {
        return camera;
    };


}
