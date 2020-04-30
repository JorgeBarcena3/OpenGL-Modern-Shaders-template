/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge on February of 2020                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "BaseModel3D.hpp"
#include <functional>

#ifndef MESH_HEADER
#define MESH_HEADER


namespace OpenGLRender3D {

    class Model3D;

    /*
    * Clase que va a manejar un modelo 3D
    */
    class Mesh
    {

    private:

        std::vector< GLuint > indices;

        Model3D* model;

        int material_index;
            

    public:

        Mesh(std::vector< GLuint > _indices, Model3D & _model, int material_index = 0);

        void render();

    };

}

#endif