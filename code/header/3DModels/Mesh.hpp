// File: Mesh.hpp
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

#include "BaseModel3D.hpp"
#include <functional>

#ifndef MESH_HEADER
#define MESH_HEADER


namespace OpenGLRender3D {

    class Model3D;

    /**
    * Componente de un modelo obj
    */
    class Mesh
    {

    private:

        std::vector< GLuint > indices; ///< Indices del modelo 3D que pertenece a la mesh

        Model3D* model;                ///< Puntero al modelo 3D al que pertenece

        int material_index;            ///< Indice del material
            

    public:

        /**
        * Constructor por defecto
        */
        Mesh(std::vector< GLuint > _indices, Model3D & _model, int material_index = 0);

        /**
        * Funcion que se va a llamar cuando se debe renderizar la mesh
        */
        void render();

    };

}

#endif