// File: Cylinder.hpp
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

#ifndef CYLINDER_HEADER
#define CYLINDER_HEADER

#include <vector>
#include "BaseModel3D.hpp"

namespace OpenGLRender3D
{

    /**
    * Genera un cilindro procedural
    */
    class Cylinder : public BaseModel3D
    {

    private:

        float radius; ///< Radio del cilindro

        float height; ///< Altura del cilindro

        float sides;  ///< Lados que tendrá el cilindro

    public:

        /**
        * Constructor del cilindro
        */
        Cylinder(float radius, float height, Scene& _scene, OpenGLRender3D::OPACITYMODEL op, float sides = 18, std::string tx_path = ConfigOptions::ConfigPaths::configSettingsMap["texture_default_path"]);
 
        /**
        * Destructor del cilindro
        */
        ~Cylinder();

        /**
        * Heredado de BaseModel3D
        * Renderiza el cilindro
        */
        void render() override;


    private:

        /**
        * Genera los vertices del cilindro
        */
        void createVertices(std::vector< GLfloat >& coordinates, std::vector< GLfloat >& normals, std::vector< GLfloat >& tx);

        /**
        * Genera los indices del cilindro
        */
        void createIndices(std::vector< GLfloat >& coordinates);
        
        /**
        * Genera los colores del cilindro
        */
        void createColors(std::vector< GLfloat >& colors, std::vector< GLfloat >& coodinates);



    };

}

#endif
