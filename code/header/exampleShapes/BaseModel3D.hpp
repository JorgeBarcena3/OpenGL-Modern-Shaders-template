
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
            VBO_COUNT
        };


    protected:

        GLuint vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan
        GLuint vao_id;                  // Id del VAO del cubo

        std::vector< GLuint > indices;

        std::vector<Texture*> textures_factory;


    public:

        Transform transform;

        Scene* scene;

        virtual void render() = 0;

        virtual void update() = 0;

        void setParent(Transform* _transform)
        {
            transform.addParent(_transform);
        }

    };

}

#endif
