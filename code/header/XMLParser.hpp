
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Copyright © 2014+ Ángel Rodríguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef XMLPARSER_SHADER_HEADER
#define XMLPARSER_SHADER_HEADER

#include <string>
#include "Scene.hpp"
#include "../rapidxml-1.13/rapidxml.hpp"
#include "../rapidxml-1.13/rapidxml_utils.hpp"

namespace OpenGLRender3D
{

    class XMLParser 
    {
    public:

        static void loadScene(std::string path, Scene& scene);
        static void parseConfig(std::string path);

        static void setConfiguration(rapidxml::xml_node<>* path);
        static void setEntities(rapidxml::xml_node<>* path, Scene& scene);
        static void setLights(rapidxml::xml_node<>* path, Scene& scene);
        
        static OpenGLRender3D::Transform parseTransfrom(rapidxml::xml_node<>* path);
        static glm::vec3 parseVec3(std::string value);

    private:

        static void setDefaultConfiguration();

    };

}

#endif
