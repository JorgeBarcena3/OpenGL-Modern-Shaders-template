
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge Barcena on March of 2020                                  *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef MALLA_HEADER
#define MALLA_HEADER

#include <vector>
#include <string>
#include "BaseModel3D.hpp"

namespace OpenGLRender3D
{

    class Malla : public BaseModel3D
    {
    private:


        float width;
        float height;
        int vertex_count;     


    public:

        Malla(float width, float height, int vertex_count, Scene& scene, OpenGLRender3D::OPACITYMODEL op, std::string path = "",  std::string tx_path = "../../assets/default/texture.tga");
        ~Malla();

        void setHeightCoordinates(std::vector< GLfloat >& coordinates, std::vector< GLfloat >& normals, std::vector< GLfloat >& tx, std::string path);
        void createVertices(std::vector< GLfloat >& coordinates, std::vector< GLfloat >& normals , std::vector< GLfloat >& tx);
        void createIndices(std::vector< GLfloat >& coordinates);
        void createColors(std::vector< GLfloat >& colors, std::vector< GLfloat >& coodinates);
        GLfloat getHeight(int x, int y, const std::vector< GLfloat >& coordinates);

        void render() override;


    };

}

#endif
