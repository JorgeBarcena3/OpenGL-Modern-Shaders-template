// File: Malla.hpp
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

#ifndef MALLA_HEADER
#define MALLA_HEADER

#include <vector>
#include <string>
#include "BaseModel3D.hpp"

namespace OpenGLRender3D
{

    /**
    * Genera una malla de elevacion partiendo de una imagen
    */
    class Malla : public BaseModel3D
    {

    private:

        float width;        ///< Anchura de la malla

        float height;       ///< Altura de la malla

        int vertex_count;   ///< Vertices de la malla

        float max_height;   ///< Altura maxima de la malla


    public:

        /**
        * Constructor de la malla de elevacion
        */
        Malla(float width, float height, float max_height, int vertex_count, Scene& scene, OpenGLRender3D::OPACITYMODEL op, std::string path = "",  std::string tx_path = ConfigOptions::ConfigPaths::configSettingsMap["texture_default_path"]);
       
        /**
        * Destructor de la malla
        */
        ~Malla();

        /**
        * Heredado de BaseModel3D
        * Renderiza la malla
        */
        void render() override;

    private:

        /**
        * Devuelve la altura de un vertice de la malla
        */
        GLfloat getHeight(int x, int y, const std::vector< GLfloat >& coordinates);

        /**
        * Determina la altura de cada vertice en la malla
        */
        void setHeightCoordinates(std::vector< GLfloat >& coordinates, std::vector< GLfloat >& normals, std::vector< GLfloat >& tx, std::string path);
        
        /**
        * Crea los vertices
        */
        void createVertices(std::vector< GLfloat >& coordinates, std::vector< GLfloat >& normals, std::vector< GLfloat >& tx);
        
        /**
        * Crea los indices
        */
        void createIndices(std::vector< GLfloat >& coordinates);
        
        /**
        * Crea los colores en cada vertice
        */
        void createColors(std::vector< GLfloat >& colors, std::vector< GLfloat >& coodinates);


    };

}

#endif
