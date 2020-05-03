
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
#include "../header/XMLParser.hpp"

// Rutas por defecto de la aplicacion
std::string ConfigOptions::ConfigPaths::texture_default_path            = "../../assets/default/texture.tga";
std::string ConfigOptions::ConfigPaths::shader_myMaterialKa             = "myMaterial.Ka";
std::string ConfigOptions::ConfigPaths::shader_myMaterialKd             = "myMaterial.Kd";
std::string ConfigOptions::ConfigPaths::shader_myMaterialKs             = "myMaterial.Ks";
std::string ConfigOptions::ConfigPaths::shader_pointLight_array         = "pointLights";
std::string ConfigOptions::ConfigPaths::shader_directionalLight_array   = "directionalLight";
std::string ConfigOptions::ConfigPaths::camera_shader_path              = "../../assets/camera/";
std::string ConfigOptions::ConfigPaths::skybox_shader_path              = "../../assets/skybox/";
std::string ConfigOptions::ConfigPaths::postprocesing_shader_path       = "../../assets/postprocessing/";
std::string ConfigOptions::ConfigPaths::vertexShader_name               = "vertexShader.vglsl";
std::string ConfigOptions::ConfigPaths::fragmentShader_name             = "fragmentShader.fglsl";
std::string ConfigOptions::ConfigPaths::shader_camera_matrix            = "camera_matrix";
std::string ConfigOptions::ConfigPaths::shader_model_matrix             = "model_matrix";
std::string ConfigOptions::ConfigPaths::shader_camera_position          = "camera_pos";
std::string ConfigOptions::ConfigPaths::skybox_path                     = "../../assets/skybox/SD/sky-cube-map-";


namespace OpenGLRender3D
{

    using namespace std;

    Scene::Scene(int width, int height, std::string path, sf::Window& _window)
    {
        XMLParser::parseConfig(path);

        window = &_window;
        window_size = (glm::vec2(width, height));
        camera = (new OpenGLRender3D::Camera(width, height, *this));
        postpoProgram = new PostprocessingProgram(*this);
        scene_Node = (new Transform());
        skybox = (new OpenGLRender3D::Skybox(ConfigOptions::ConfigPaths::skybox_path, *this));


        XMLParser::loadScene(path, *this);       
        orderEntitiesTransparency();

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

        postpoProgram->activeCurrentFrameBuffer();

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

        postpoProgram->render();

    }

    void Scene::cleanActionsPool()
    {
        for each (auto action in actionsPool)
        {
            if (action.first == "Mover Camara")
            {
                camera->moveCamera(action.second);
            }
            else if (action.first == "Postproceso")
            {
                postpoProgram->toggleActive();
            }
        }


        actionsPool.clear();
    }

    bool Scene::manageInput(sf::Window& window)
    {
        sf::Event event;

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
                window_size = glm::vec2((int)window.getSize().x, (int)window.getSize().y);

                getMainCamera()->resize((int)window_size.x, (int)window_size.y);
                postpoProgram->resize((int)window_size.x, (int)window_size.y);

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
                else if (event.key.code == sf::Keyboard::P)
                {
                    actionsPool.emplace("Postproceso", glm::vec3());
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

    void Scene::addEntity(std::string name, BaseModel3D * entity)
    {
        entities[name] = entity;
    }

    void Scene::addLight(std::string name, Light* light)
    {
        lights[name] = light;

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
