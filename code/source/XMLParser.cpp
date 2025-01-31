#include "../header/XMLParser.hpp"
#include "../header/ConfigOptions.hpp"
#include "../header/3DModels/Model3D.hpp"
#include "../header/3DModels/Malla.hpp"
#include "../header/3DModels/Cylinder.hpp"
#include "../header/Transform.hpp"
#include "../header/DirectionalLight.hpp"
#include "../header/PointLight.hpp"

#include <sstream>      // std::stringstream


std::string OpenGLRender3D::XMLParser::XMLPath = "";

void OpenGLRender3D::XMLParser::loadScene(std::string path, Scene& scene)
{

    XMLPath = path.substr(0, path.find_last_of("/\\")) + "/";

    rapidxml::file<> xmlFile(path.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    auto rootNode = doc.first_node();

    scene.sceneTitle = rootNode->first_attribute("WindowName")->value();

    for (rapidxml::xml_node<>* entityNode = rootNode->first_node(); entityNode; entityNode = entityNode->next_sibling()) //Son las entidades
    {
        auto name = std::string(entityNode->name());

        if (name.compare("Entity") == 0)
        {
            setEntities(entityNode, scene);

        }
        else if (name.compare("Light") == 0)
        {
            setLights(entityNode, scene);
        }


    }
}

void OpenGLRender3D::XMLParser::parseConfig(std::string path)
{

    XMLPath = path.substr(0, path.find_last_of("/\\")) + "/";

    setDefaultConfiguration();

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

    if (name.find("path") != std::string::npos)
        ConfigOptions::ConfigPaths::configSettingsMap[name] = XMLPath + value;

    else
        ConfigOptions::ConfigPaths::configSettingsMap[name] = value;


}

void OpenGLRender3D::XMLParser::setEntities(rapidxml::xml_node<>* element, Scene& scene)
{
    std::string name = element->first_attribute("name")->value();
    std::string type = element->first_attribute("type")->value();
    std::string parent = element->first_attribute("parent") ? element->first_attribute("parent")->value() : "root";

    if (type == "Model3D")
    {
        std::string path = element->first_attribute("objPath") ? XMLPath + element->first_attribute("objPath")->value() : ConfigOptions::ConfigPaths::configSettingsMap["texture_default_path"];
        OpenGLRender3D::OPACITYMODEL opacity = element->first_attribute("opacity")->value() == "Translucid" ? OpenGLRender3D::OPACITYMODEL::TRANSLUCID : OpenGLRender3D::OPACITYMODEL::OPAQUE;
        Transform  transform = parseTransfrom(element);

        scene.addEntity(name, new OpenGLRender3D::Model3D(scene, opacity, (path).c_str()));

        scene.getEntity(name)->transform.setPosition(transform.getPosition());
        scene.getEntity(name)->transform.setRotation(transform.getRotation());
        scene.getEntity(name)->transform.setScale(transform.getScale());

    }
    else if (type == "Cylinder")
    {
        std::string radius = element->first_attribute("radius")->value();
        std::string height = element->first_attribute("height")->value();
        std::string sides = element->first_attribute("sides")->value();
        std::string path = element->first_attribute("texturePath") ? XMLPath + element->first_attribute("texturePath")->value() : ConfigOptions::ConfigPaths::configSettingsMap["texture_default_path"];

        OpenGLRender3D::OPACITYMODEL opacity = (std::string("Translucid").compare(element->first_attribute("opacity")->value()) == 0) ? OpenGLRender3D::OPACITYMODEL::TRANSLUCID : OpenGLRender3D::OPACITYMODEL::OPAQUE;
        Transform  transform = parseTransfrom(element);

        scene.addEntity(name, new OpenGLRender3D::Cylinder(std::atof(radius.c_str()), std::atof(height.c_str()), scene, opacity, std::atof(sides.c_str()), (path)));

        scene.getEntity(name)->transform.setPosition(transform.getPosition());
        scene.getEntity(name)->transform.setRotation(transform.getRotation());
        scene.getEntity(name)->transform.setScale(transform.getScale());

    }
    else if (type == "Malla")
    {


        std::string width = element->first_attribute("width")->value();
        std::string height = element->first_attribute("height")->value();
        std::string vertex = element->first_attribute("vertex")->value();
        std::string max_height = element->first_attribute("max-height") ? element->first_attribute("max-height")->value() : "3";
        std::string heightMap = element->first_attribute("heightMap") ? XMLPath + element->first_attribute("heightMap")->value() : "";
        std::string textureMap = element->first_attribute("texturePath") ? XMLPath  + element->first_attribute("texturePath")->value() : ConfigOptions::ConfigPaths::configSettingsMap["texture_default_path"];

        OpenGLRender3D::OPACITYMODEL opacity = element->first_attribute("opacity")->value() == "Translucid" ? OpenGLRender3D::OPACITYMODEL::TRANSLUCID : OpenGLRender3D::OPACITYMODEL::OPAQUE;
        Transform  transform = parseTransfrom(element);

        scene.addEntity(name, new OpenGLRender3D::Malla(
            std::atof(width.c_str()),
            std::atof(height.c_str()),
            std::atof(max_height.c_str()),
            std::atoi(vertex.c_str()),
            scene,
            opacity,
            (heightMap).c_str(),
            (textureMap).c_str()
        ));

        scene.getEntity(name)->transform.setPosition(transform.getPosition());
        scene.getEntity(name)->transform.setRotation(transform.getRotation());
        scene.getEntity(name)->transform.setScale(transform.getScale());

    }

    scene.getEntity(name)->setParent(parent != "root" ? &scene.getEntity(parent)->transform : scene.scene_Node);

}

void OpenGLRender3D::XMLParser::setLights(rapidxml::xml_node<>* element, Scene& scene)
{

    std::string name = element->first_attribute("name")->value();
    std::string type = element->first_attribute("type")->value();
    std::string eneabled = element->first_attribute("eneabled")->value();


    if (type == "Directional")
    {

        glm::vec3 direction = parseVec3(element->first_attribute("direction")->value());

        scene.addLight(name, new OpenGLRender3D::DirectionalLight(
            direction,
            scene
        ));

        scene.getLight(name)->setEneabled(std::atoi(eneabled.c_str()));


        for (rapidxml::xml_node<>* entityNode = element->first_node(); entityNode; entityNode = entityNode->next_sibling()) //Son las entidades
        {
            std::string attrb = entityNode->name();
            glm::vec3 value = parseVec3(entityNode->value());

            if (attrb == "Color")
            {
                scene.getLight(name)->setColor(value);
            }
            else if (attrb == "Intensity")
            {
                scene.getLight(name)->setIntensity(value);
            }
            else if (attrb == "Ambient")
            {
                scene.getLight(name)->setAmbientColor(value);
            }
            else if (attrb == "Diffuse")
            {
                scene.getLight(name)->setdiffuseColor(value);
            }
            else if (attrb == "Specular")
            {
                scene.getLight(name)->setSpecularColor(value);
            }


        }

        scene.getLight(name)->getUniformId(scene.camera->getShaderProgram(), std::to_string(DirectionalLight::light_id++));
        scene.getLight(name)->setUniformVariables(scene.camera->getShaderProgram());
    }
    else if (type == "PointLight")
    {

        glm::vec3 position = parseVec3(element->first_attribute("position")->value());

        scene.addLight(name, new OpenGLRender3D::PointLight(
            position,
            scene
        ));

        scene.getLight(name)->setEneabled(std::atoi(eneabled.c_str()));


        for (rapidxml::xml_node<>* entityNode = element->first_node(); entityNode; entityNode = entityNode->next_sibling()) //Son las entidades
        {
            std::string attrb = entityNode->name();
            glm::vec3 value = parseVec3(entityNode->value());

            if (attrb == "Color")
            {
                scene.getLight(name)->setColor(value);
            }
            else if (attrb == "Intensity")
            {
                scene.getLight(name)->setIntensity(value);
            }
            else if (attrb == "Ambient")
            {
                scene.getLight(name)->setAmbientColor(value);
            }
            else if (attrb == "Diffuse")
            {
                scene.getLight(name)->setdiffuseColor(value);
            }
            else if (attrb == "Specular")
            {
                scene.getLight(name)->setSpecularColor(value);
            }
        }

        scene.getLight(name)->getUniformId(scene.camera->getShaderProgram(), std::to_string(PointLight::light_id++));
        scene.getLight(name)->setUniformVariables(scene.camera->getShaderProgram());
    }


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

void OpenGLRender3D::XMLParser::setDefaultConfiguration()
{
    ConfigOptions::ConfigPaths::configSettingsMap["texture_default_path"] = "default/texture.tga";
    ConfigOptions::ConfigPaths::configSettingsMap["shader_myMaterialKa"] = "myMaterial.Ka";
    ConfigOptions::ConfigPaths::configSettingsMap["shader_myMaterialKd"] = "myMaterial.Kd";
    ConfigOptions::ConfigPaths::configSettingsMap["shader_myMaterialKs"] = "myMaterial.Ks";
    ConfigOptions::ConfigPaths::configSettingsMap["shader_pointLight_array"] = "pointLights";
    ConfigOptions::ConfigPaths::configSettingsMap["shader_directionalLight_array"] = "directionalLight";
    ConfigOptions::ConfigPaths::configSettingsMap["camera_shader_path"] = "camera/";
    ConfigOptions::ConfigPaths::configSettingsMap["skybox_shader_path"] = "skybox/";
    ConfigOptions::ConfigPaths::configSettingsMap["postprocesing_shader_path"] = "postprocessing/blur";
    ConfigOptions::ConfigPaths::configSettingsMap["vertexShader_name"] = "vertexShader.vglsl";
    ConfigOptions::ConfigPaths::configSettingsMap["fragmentShader_name"] = "fragmentShader.fglsl";
    ConfigOptions::ConfigPaths::configSettingsMap["shader_camera_matrix"] = "camera_matrix";
    ConfigOptions::ConfigPaths::configSettingsMap["shader_model_matrix"] = "model_matrix";
    ConfigOptions::ConfigPaths::configSettingsMap["shader_camera_position"] = "camera_pos";
    ConfigOptions::ConfigPaths::configSettingsMap["skybox_path"] = "skybox/SD/sky-cube-map-";

}


