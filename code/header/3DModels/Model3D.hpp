// File: Model3D.hpp
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
#include <vector>
#include "Mesh.hpp"

#ifndef MODEL3D_HEADER
#define MODEL3D_HEADER


namespace OpenGLRender3D {    

    /**
    * Clase que va a manejar un modelo 3D
    */
    class Model3D : public BaseModel3D
    {

    private:

        friend class Mesh;

        std::vector<Mesh*> meshes; ///< Meshes que tiene atachado


    public:

        /**
        * Crea un modelo 3D
        */
        Model3D(Scene& scene, OpenGLRender3D::OPACITYMODEL op, const char* path);

        /**
        * Destructor del modelo 3D
        */
        ~Model3D();

        /**
        * Heredado de BaseModel3D
        * Renderiza todas las meshes que tiene
        */
        virtual void render() override;



    private:

        /**
        * Carga un obj
        */
        void loadObj(const char* path);

    };

}

#endif