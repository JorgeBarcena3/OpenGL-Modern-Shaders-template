#include "XMLParser.hpp"
#include "ConfigOptions.hpp"
#include "3DModels/Model3D.hpp"
#include "3DModels/Malla.hpp"
#include "3DModels/Cylinder.hpp"
#include "Transform.hpp"
#include "DirectionalLight.hpp"

#include <sstream>      // std::stringstream



void OpenGLRender3D::XMLParser::loadScene(std::string path, Scene& scene)
{

    rapidxml::file<> xmlFile(path.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    auto rootNode = doc.first_node();

    scene.window->setTitle(rootNode->first_attribute("WindowName")->value());

    for (rapidxml::xml_node<>* entityNode = rootNode->first_node(); entityNode; entityNode = entityNode->next_sibling()) //Son las entidades
    {
        auto name = std::string(entityNode->name());

        if (name.compare("Entity") == 0)
        {
            setEntities(entityNode, scene);

        }
        else if (name.compare("Light") == 0)
        {
            setLights(entityNode->first_node(), scene);
        }


    }
}

void OpenGLRender3D::XMLParser::parseConfig(std::string path)
{
    rapidxml::file<> xmlFile(path.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    auto rootNode = doc.first_node();

    for (rapidxml::xml_node<>* entityNode = rootNode->first_node(); entityNode; entityNode = entityNode->next_sibling()) //Son las entidades
    {
        auto name = std::string(entityNode->name());

        if (name.compare("Configuration") == 0)
        {
            setConfiguration(entityNode);
        }


    }
}

void OpenGLRender3D::XMLParser::setConfiguration(rapidxml::xml_node<>* element)
{


    std::string name = element->first_attribute("name")->value();
    std::string value = element->first_attribute("value")->value();

    if (name == "texture_default_path")
    {
        ConfigOptions::ConfigPaths::texture_default_path = value;
    }
    else if (name == "shader_myMaterialKa") {
        ConfigOptions::ConfigPaths::shader_myMaterialKa = value;
    }
    else if (name == "shader_myMaterialKd") {
        ConfigOptions::ConfigPaths::shader_myMaterialKd = value;
    }
    else if (name == "shader_myMaterialKs") {
        ConfigOptions::ConfigPaths::shader_myMaterialKs = value;
    }
    else if (name == "shader_pointLight_array") {
        ConfigOptions::ConfigPaths::shader_pointLight_array = value;
    }
    else if (name == "shader_directionalLight_array") {
        ConfigOptions::ConfigPaths::shader_directionalLight_array = value;
    }
    else if (name == "camera_shader_path") {
        ConfigOptions::ConfigPaths::camera_shader_path = value;
    }
    else if (name == "skybox_shader_path") {
        ConfigOptions::ConfigPaths::skybox_shader_path = value;
    }
    else if (name == "skybox_path") {
        ConfigOptions::ConfigPaths::skybox_path = value;
    }
    else if (name == "postprocesing_shader_path") {
        ConfigOptions::ConfigPaths::postprocesing_shader_path = value;
    }
    else if (name == "vertexShader_name") {
        ConfigOptions::ConfigPaths::vertexShader_name = value;
    }
    else if (name == "fragmentShader_name") {
        ConfigOptions::ConfigPaths::fragmentShader_name = value;
    }
    else if (name == "shader_camera_matrix") {
        ConfigOptions::ConfigPaths::shader_camera_matrix = value;
    }
    else if (name == "shader_model_matrix") {
        ConfigOptions::ConfigPaths::shader_model_matrix = value;
    }
    else if (name == "shader_camera_position") {
        ConfigOptions::ConfigPaths::shader_camera_position = value;
    }

}

void OpenGLRender3D::XMLParser::setEntities(rapidxml::xml_node<>* element, Scene& scene)
{
    std::string name = element->first_attribute("name")->value();
    std::string type = element->first_attribute("type")->value();

    if (type == "Model3D")
    {
        std::string path = element->first_attribute("objPath") ? element->first_attribute("objPath")->value() : ConfigOptions::ConfigPaths::texture_default_path;
        OpenGLRender3D::OPACITYMODEL opacity = element->first_attribute("opacity")->value() == "Translucid" ? OpenGLRender3D::OPACITYMODEL::TRANSLUCID : OpenGLRender3D::OPACITYMODEL::OPAQUE;
        Transform  transform = parseTransfrom(element);

        scene.addEntity(name, new OpenGLRender3D::Model3D(scene, opacity, path.c_str()));

        scene.getEntity(name)->transform.setPosition(transform.getPosition());
        scene.getEntity(name)->transform.setRotation(transform.getRotation());
        scene.getEntity(name)->transform.setScale(transform.getScale());

    }
    else if (type == "Cylinder")
    {
        std::string radius = element->first_attribute("radius")->value();
        std::string height = element->first_attribute("height")->value();
        std::string sides = element->first_attribute("sides")->value();
        std::string path = element->first_attribute("path") ? element->first_attribute("path")->value() : ConfigOptions::ConfigPaths::texture_default_path;


        OpenGLRender3D::OPACITYMODEL opacity = element->first_attribute("opacity")->value() == "Translucid" ? OpenGLRender3D::OPACITYMODEL::TRANSLUCID : OpenGLRender3D::OPACITYMODEL::OPAQUE;
        Transform  transform = parseTransfrom(element);

        scene.addEntity(name, new OpenGLRender3D::Cylinder(std::atof(radius.c_str()), std::atof(height.c_str()), scene, opacity, std::atof(sides.c_str()), path));

        scene.getEntity(name)->transform.setPosition(transform.getPosition());
        scene.getEntity(name)->transform.setRotation(transform.getRotation());
        scene.getEntity(name)->transform.setScale(transform.getScale());

    }
    else if (type == "Malla")
    {


        std::string width = element->first_attribute("width")->value();
        std::string height = element->first_attribute("height")->value();
        std::string vertex = element->first_attribute("vertex")->value();
        std::string heightMap = element->first_attribute("heightMap")->value() ? element->first_attribute("heightMap")->value() : "";
        std::string textureMap = element->first_attribute("textureMap") ? element->first_attribute("textureMap")->value() : ConfigOptions::ConfigPaths::texture_default_path;

        OpenGLRender3D::OPACITYMODEL opacity = element->first_attribute("opacity")->value() == "Translucid" ? OpenGLRender3D::OPACITYMODEL::TRANSLUCID : OpenGLRender3D::OPACITYMODEL::OPAQUE;
        Transform  transform = parseTransfrom(element);

        scene.addEntity(name, new OpenGLRender3D::Malla(
            std::atof(width.c_str()),
            std::atof(height.c_str()),
            std::atoi(vertex.c_str()),
            scene,
            opacity,
            heightMap.c_str(),
            textureMap.c_str()
        ));

        scene.getEntity(name)->transform.setPosition(transform.getPosition());
        scene.getEntity(name)->transform.setRotation(transform.getRotation());
        scene.getEntity(name)->transform.setScale(transform.getScale());

    }

}

void OpenGLRender3D::XMLParser::setLights(rapidxml::xml_node<>* element, Scene& scene)
{

    std::string name = element->first_attribute("name")->value();
    std::string type = element->first_attribute("type")->value();

    if (type == "Directional")
    {

        std::string eneabled = element->first_attribute("Eneabled")->value();
        glm::vec3 direction = parseVec3(element->first_attribute("Direction")->value());

        scene.addLight(name, new OpenGLRender3D::DirectionalLight(
            direction,
            scene
        ));

        scene.getLight(name)->setEneabled(std::atoi(eneabled.c_str()));


        for (rapidxml::xml_node<>* entityNode = element->first_node(); entityNode; entityNode = entityNode->next_sibling()) //Son las entidades
        {
            std::string name = entityNode->name();
            glm::vec3 value = parseVec3(entityNode->value());

            if (name == "Color")
            {
                scene.getLight(name)->setColor(value);
            }
            else if (name == "Intensity")
            {
                scene.getLight(name)->setIntensity(value);
            } 
            else if (name == "Ambient")
            {
                scene.getLight(name)->setAmbientColor(value);
            } 
            else if (name == "Diffuse")
            {
                scene.getLight(name)->setdiffuseColor(value);
            } 
            else if (name == "Specular")
            {
                scene.getLight(name)->setSpecularColor(value);
            }


        }
       
    }

    // CREAR VARIABLE ESTATICA PARA LLEVAR EL CONTEO DE LAS LUCES
    scene.getLight(name)->getUniformId(scene.camera->getShaderProgram(), id);
    scene.getLight(name)->setUniformVariables(scene.camera->getShaderProgram());

}

OpenGLRender3D::Transform OpenGLRender3D::XMLParser::parseTransfrom(rapidxml::xml_node<>* element)
{

    Transform myTransform;

    for (rapidxml::xml_node<>* entityNode = element->first_node(); entityNode; entityNode = entityNode->next_sibling()) //Son las entidades
    {
        std::string name = entityNode->name();
        std::string value = entityNode->value();


        std::stringstream test(value);
        std::string segment;
        std::vector<std::string> seglist;

        while (std::getline(test, segment, ','))
        {
            seglist.push_back(segment);
        }

        if (name == "Position")
        {
            myTransform.setPosition(glm::vec3(std::stof(seglist[0]), std::stof(seglist[1]), std::stof(seglist[2])));
        }
        else if (name == "Rotation")
        {
            myTransform.setRotation(glm::vec3(std::stof(seglist[0]), std::stof(seglist[1]), std::stof(seglist[2])));

        }
        else if (name == "Scale")
        {
            myTransform.setScale(glm::vec3(std::stof(seglist[0]), std::stof(seglist[1]), std::stof(seglist[2])));

        }

    }


    return myTransform;

}

glm::vec3 OpenGLRender3D::XMLParser::parseVec3(std::string value)
{

    std::stringstream test(value);
    std::string segment;
    std::vector<std::string> seglist;

    while (std::getline(test, segment, ','))
    {
        seglist.push_back(segment);
    }

    return glm::vec3(std::stof(seglist[0]), std::stof(seglist[1]), std::stof(seglist[2]));
}


