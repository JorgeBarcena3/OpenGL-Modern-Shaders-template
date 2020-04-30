
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef BASESHAPES_HEADER
#define BASESHAPES_HEADER

#include <memory>
#include <vector>
#include <cmath>
#include <SFML/OpenGL.hpp>
#include "../Scene.hpp"
#include "../Transform.hpp"

namespace OpenGLRender3D
{

    class Texture;

    class BaseModel3D
    {

    protected:


        // Índices para indexar el array vbo_ids:

        enum
        {
            COORDINATES_VBO,
            COLORS_VBO,
            NORMALS_VBO,
            TEXTURE_VBO,
            INDICES_IBO,
            TEXTURE_COORD,
            VBO_COUNT
        };


    protected:

        GLuint vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan
        GLuint vao_id;                  // Id del VAO del cubo

    public:

        Transform transform;

        Scene* scene;

        Texture * texture;

        virtual void render() = 0;

        virtual void update() = 0;


    };

}

#endif
