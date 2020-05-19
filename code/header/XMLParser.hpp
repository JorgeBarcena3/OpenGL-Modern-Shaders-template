// File: XMLParser.hpp
// Author: Jorge Bárcena Lumbreras

// © Copyright (C) 2020  Jorge Bárcena Lumbreras

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef XMLPARSER_SHADER_HEADER
#define XMLPARSER_SHADER_HEADER

#include <string>
#include "Scene.hpp"
#include "../rapidxml-1.13/rapidxml.hpp"
#include "../rapidxml-1.13/rapidxml_utils.hpp"

namespace OpenGLRender3D
{

    /**
    * Parsea un archivo XML y lo manda a la escena
    */
    class XMLParser 
    {
    public:


        /**
        * Carga la escena
        */
        static void loadScene(std::string path, Scene& scene);

        /**
        * Carga las configuraciones de la aplicacion
        */
        static void parseConfig(std::string path);

        /**
        * Determina el valor de un nodo de configuracion
        */
        static void setConfiguration(rapidxml::xml_node<>* path);

        /**
        * Añade una entidad a la escena
        */
        static void setEntities(rapidxml::xml_node<>* path, Scene& scene);

        /**
        * Añade una luz a la escena
        */
        static void setLights(rapidxml::xml_node<>* path, Scene& scene);

        /**
        * Parsea el componente transform de cada entidad
        */
        static OpenGLRender3D::Transform parseTransfrom(rapidxml::xml_node<>* path);

        /**
        * Parsea un nodo con tres valroes a un vector3
        */
        static glm::vec3 parseVec3(std::string value);

    private:


        /**
        * Configuracion por defecto
        */
        static void setDefaultConfiguration();


        /**
        * Path del archivo XML
        */
        static std::string XMLPath;

    };

}

#endif
