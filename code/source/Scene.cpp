
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <cassert>
#include <SFML/Window/Mouse.hpp>

#include "../header/Scene.hpp"
#include "../header/exampleShapes/Malla.hpp"
#include "../header/exampleShapes/Model3D.hpp"
#include "../header/Camera.hpp"
#include "../header/DirectionalLight.hpp"
#include "../header/PointLight.hpp"
#include "../header/exampleShapes/Skybox.hpp"
#include "../header/exampleShapes/Cylinder.hpp" 


namespace OpenGLRender3D
{

    using namespace std;

    Scene::Scene(int width, int height) :
        scene_Node(new Transform()),
        camera(new OpenGLRender3D::Camera(width, height, *this)),
        skybox(new OpenGLRender3D::Skybox("../../assets/skybox/SD/sky-cube-map-", *this)),
        window_size(glm::vec2(width, height))
    {

        configureEntities();

        configureLights();

    }

    void Scene::update(float time)
    {

        cleanActionsPool();

        skybox->update(time);

        camera->update(time);

        for (auto light : lights)
        {
            light.second->update(time);
        }

        for (auto shape : entities)
        {
            shape.second->update(time);
        }

    }

    void Scene::render()
    {


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.5f, 0.5f, 0.5f, 1.f);

        skybox->render();

        camera->render();

        //Se renderizan las entidades opacas
        for (auto entity : opaque)
        {
            entity->render();
        }

        //Se renderizan las entidades translucidas
        orderEntitiesByDistanceCamera(translucid);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);

        for (auto enety : translucid)
        {
            enety->render();
        }

        glDisable(GL_BLEND);

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
                    actionsPool.emplace("Mover Camara", camera->cameraTransformAttributes.front);
                }
                else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                {
                    actionsPool.emplace("Mover Camara", -camera->cameraTransformAttributes.front);
                }

                if (event.key.code == sf::Keyboard::Space)
                {
                    actionsPool.emplace("Mover Camara", camera->cameraTransformAttributes.worldUp);
                }
                else if (event.key.code == sf::Keyboard::LControl)
                {
                    actionsPool.emplace("Mover Camara", -camera->cameraTransformAttributes.worldUp);
                }

                if (event.key.code == sf::Keyboard::A)
                {
                    actionsPool.emplace("Mover Camara", -camera->cameraTransformAttributes.right);
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    actionsPool.emplace("Mover Camara", camera->cameraTransformAttributes.right);
                }
            }

            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            camera->rotateCamera(pos);
        }
        else if (!camera->mousePosition.firstPressed)
        {
            camera->mousePosition.firstPressed = true;
        }

        return true;
    }

    Camera* Scene::getMainCamera()
    {
        return camera;
    }

    void Scene::configureLights()
    {
        int index = 0;

        lights.emplace("Sun", new PointLight(glm::vec3(-1, 1, -1), *this));

        lights["Sun"]->setEneabled(1);
        lights["Sun"]->setColor(glm::vec3(1, 0, 0));
        lights["Sun"]->setIntensity(glm::vec3(2));
        lights["Sun"]->setAmbientColor(glm::vec3(0.25f));
        lights["Sun"]->setdiffuseColor(glm::vec3(0.5f));
        lights["Sun"]->setSpecularColor(glm::vec3(0.25f));
        lights["Sun"]->getUniformId(camera->getShaderProgram(), std::to_string(index));
        lights["Sun"]->setUniformVariables(camera->getShaderProgram());

        index = 0;

        lights.emplace("Point Light 1", new DirectionalLight(glm::vec3(-1, 2, -1), *this));
        lights["Point Light 1"]->setEneabled(1);
        lights["Point Light 1"]->setIntensity(glm::vec3(2));
        lights["Point Light 1"]->setColor(glm::vec3(1, 1, 1));
        lights["Point Light 1"]->setAmbientColor(glm::vec3(0.1f));
        lights["Point Light 1"]->setdiffuseColor(glm::vec3(0.9f));
        lights["Point Light 1"]->setSpecularColor(glm::vec3(0.f));
        lights["Point Light 1"]->getUniformId(camera->getShaderProgram(), std::to_string(index));
        lights["Point Light 1"]->setUniformVariables(camera->getShaderProgram());


    }

    void Scene::configureEntities()
    {
        entities.emplace("Terreno", new OpenGLRender3D::Malla(25, 25, 256, *this, OPACITYMODEL::OPAQUE, "../../assets/height_map/Volcan.tga", "../../assets/default/tx_colors.tga"));
        getEntity("Terreno")->setParent(scene_Node);

        entities.emplace("Calavera", new OpenGLRender3D::Model3D(*this, OPACITYMODEL::OPAQUE, "../../assets/models/skull/12140_Skull_v3_L2.obj"));
        getEntity("Calavera")->transform.setPosition(glm::vec3(0, 0, -15));
        getEntity("Calavera")->transform.setScale(glm::vec3(0.1f, 0.1f, 0.1f));
        getEntity("Calavera")->setParent(scene_Node);

        /*    entities.emplace("Calavera1", new OpenGLRender3D::Model3D(*this, OPACITYMODEL::TRANSLUCID, "../../assets/models/skull/12140_Skull_v3_L2.obj"));
            getEntity("Calavera1")->transform.setPosition(glm::vec3(0, 0, -10));
            getEntity("Calavera1")->transform.setScale(glm::vec3(0.1f, 0.1f, 0.1f));
            getEntity("Calavera1")->transform.setRotation(glm::vec3(90.f, 0, 0));
            getEntity("Calavera1")->setParent(scene_Node);

            entities.emplace("Calavera2", new OpenGLRender3D::Model3D(*this, OPACITYMODEL::TRANSLUCID, "../../assets/models/skull/12140_Skull_v3_L2.obj"));
            getEntity("Calavera2")->transform.setPosition(glm::vec3(0, 0, -35));
            getEntity("Calavera2")->transform.setScale(glm::vec3(0.1f, 0.1f, 0.1f));
            getEntity("Calavera2")->transform.setRotation(glm::vec3(90.f, 0, 0));
            getEntity("Calavera2")->setParent(scene_Node);

            entities.emplace("Calavera3", new OpenGLRender3D::Model3D(*this, OPACITYMODEL::TRANSLUCID, "../../assets/models/skull/12140_Skull_v3_L2.obj"));
            getEntity("Calavera3")->transform.setPosition(glm::vec3(0, 5, -20));
            getEntity("Calavera3")->transform.setScale(glm::vec3(0.1f, 0.1f, 0.1f));
            getEntity("Calavera3")->transform.setRotation(glm::vec3(90.f, 0, 0));
            getEntity("Calavera3")->setParent(scene_Node);*/

            //entities.emplace("Calavera4", new OpenGLRender3D::Cylinder(1, 2, *this, OPACITYMODEL::TRANSLUCID, 18, "../../assets/default/texture_alpha.tga"));
            //getEntity("Calavera4")->transform.setPosition(glm::vec3(0, 0, -5));
            //getEntity("Calavera4")->transform.setScale(glm::vec3(1));
            //getEntity("Calavera4")->transform.setRotation(glm::vec3(0, 0, 0));
            //getEntity("Calavera4")->setParent(scene_Node);


        orderEntitiesTransparency();
    }

    void Scene::orderEntitiesTransparency()
    {


        for (auto i = entities.begin(); i != entities.end(); ++i)
        {
            if (i->second->getOpacityModel() == OPACITYMODEL::OPAQUE)
            {
                opaque.push_back(i->second);
            }
            else
            {
                translucid.push_back(i->second);
            }
        }

        orderEntitiesByDistanceCamera(translucid);

    }

    void Scene::orderEntitiesByDistanceCamera(std::vector< BaseModel3D*>& toOrder)
    {
        std::map<float, BaseModel3D* > sorted;

        for (unsigned int i = 0; i < toOrder.size(); i++)
        {
            float distance = glm::length(camera->transform.getPosition() - toOrder[i]->transform.getPosition());
            sorted[distance] = toOrder[i];
        }

        toOrder.clear();

        for (auto it = sorted.rbegin(); it != sorted.rend(); ++it)
        {
            toOrder.push_back(it->second);
        }

    }

}
