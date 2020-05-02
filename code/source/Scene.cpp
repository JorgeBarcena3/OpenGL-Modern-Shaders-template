
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
#include "../header/3DModels/Malla.hpp"
#include "../header/3DModels/Model3D.hpp"
#include "../header/Camera.hpp"
#include "../header/DirectionalLight.hpp"
#include "../header/PointLight.hpp"
#include "../header/3DModels/Skybox.hpp"
#include "../header/3DModels/Cylinder.hpp" 

// Rutas por defecto de la aplicacion
std::string ConfigOptions::ConfigPaths::texture_default_path = "../../assets/default/texture.tga";
std::string ConfigOptions::ConfigPaths::shader_myMaterialKa = "myMaterial.Ka";
std::string ConfigOptions::ConfigPaths::shader_myMaterialKd = "myMaterial.Kd";
std::string ConfigOptions::ConfigPaths::shader_myMaterialKs = "myMaterial.Ks";
std::string ConfigOptions::ConfigPaths::shader_pointLight_array = "pointLights";
std::string ConfigOptions::ConfigPaths::shader_directionalLight_array = "directionalLight";
std::string ConfigOptions::ConfigPaths::camera_shader_path = "../../assets/camera/";
std::string ConfigOptions::ConfigPaths::skybox_shader_path = "../../assets/skybox/";
std::string ConfigOptions::ConfigPaths::postprocesing_shader_path = "../../assets/postprocessing/";
std::string ConfigOptions::ConfigPaths::vertexShader_name = "vertexShader.vglsl";
std::string ConfigOptions::ConfigPaths::fragmentShader_name = "fragmentShader.fglsl";

namespace OpenGLRender3D
{

    using namespace std;

    Scene::Scene(int width, int height) :
        window_size(glm::vec2(width, height)),
        postpoProgram(*this),
        scene_Node(new Transform()),
        camera(new OpenGLRender3D::Camera(width, height, *this)),
        skybox(new OpenGLRender3D::Skybox("../../assets/skybox/SD/sky-cube-map-", *this))

    {

        configureEntities();

        configureLights();

    }

    Scene::~Scene()
    {
        delete camera;
        delete skybox;

        for (auto entity : entities)
        {
            delete entity.second;
        }

        for (auto light : lights)
        {
            delete light.second;
        }

        delete scene_Node;
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

        postpoProgram.activeCurrentFrameBuffer();

        glEnable(GL_DEPTH_TEST); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

        postpoProgram.render();

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

        lights.emplace("Camera Main Light", new PointLight(glm::vec3(-1, 1, -1), *this));
        lights["Camera Main Light"]->setEneabled(1);
        lights["Camera Main Light"]->setColor(glm::vec3(1, 0, 0));
        lights["Camera Main Light"]->setIntensity(glm::vec3(2));
        lights["Camera Main Light"]->setAmbientColor(glm::vec3(0.1f));
        lights["Camera Main Light"]->setdiffuseColor(glm::vec3(0.0f));
        lights["Camera Main Light"]->setSpecularColor(glm::vec3(0.25f));
        lights["Camera Main Light"]->getUniformId(camera->getShaderProgram(), std::to_string(index));
        lights["Camera Main Light"]->setUniformVariables(camera->getShaderProgram());

        index = 0;

        lights.emplace("Main Directional Light", new DirectionalLight(glm::vec3(-10, -10, -1), *this));
        lights["Main Directional Light"]->setEneabled(1);
        lights["Main Directional Light"]->setIntensity(glm::vec3(1));
        lights["Main Directional Light"]->setColor(glm::vec3(1, 1, 1));
        lights["Main Directional Light"]->setAmbientColor(glm::vec3(0.1f));
        lights["Main Directional Light"]->setdiffuseColor(glm::vec3(0.9f));
        lights["Main Directional Light"]->setSpecularColor(glm::vec3(0.f));
        lights["Main Directional Light"]->getUniformId(camera->getShaderProgram(), std::to_string(index));
        lights["Main Directional Light"]->setUniformVariables(camera->getShaderProgram());


    }

    void Scene::configureEntities()
    {
        entities.emplace("Terreno", new OpenGLRender3D::Malla(25, 25, 256, *this, OPACITYMODEL::OPAQUE, "../../assets/height_map/Volcan.tga", "../../assets/default/tx_colors.tga"));
        getEntity("Terreno")->setParent(scene_Node);

        entities.emplace("Calavera", new OpenGLRender3D::Model3D(*this, OPACITYMODEL::OPAQUE, "../../assets/models/skull/12140_Skull_v3_L2.obj"));
        getEntity("Calavera")->transform.setPosition(glm::vec3(0, 0, -15));
        getEntity("Calavera")->transform.setScale(glm::vec3(0.1f, 0.1f, 0.1f));
        getEntity("Calavera")->setParent(scene_Node);

        entities.emplace("Cilindro", new OpenGLRender3D::Cylinder(2, 2, *this, OPACITYMODEL::OPAQUE, 18));
        getEntity("Cilindro")->transform.setPosition(glm::vec3(0, 0, -15));
        getEntity("Cilindro")->transform.setScale(glm::vec3(1));
        getEntity("Cilindro")->setParent(scene_Node);

        entities.emplace("Calavera1", new OpenGLRender3D::Model3D(*this, OPACITYMODEL::OPAQUE, "../../assets/models/skull/12140_Skull_v3_L2.obj"));
        getEntity("Calavera1")->transform.setPosition(glm::vec3(0, 0, -10));
        getEntity("Calavera1")->transform.setScale(glm::vec3(0.1f, 0.1f, 0.1f));
        getEntity("Calavera1")->transform.setRotation(glm::vec3(90.f, 0, 0));
        getEntity("Calavera1")->setParent(scene_Node);




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
