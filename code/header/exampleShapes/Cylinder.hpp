
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge Barcena on March of 2020                                  *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CYLINDER_HEADER
#define CYLINDER_HEADER

#include <vector>
#include "BaseModel3D.hpp"

namespace OpenGLRender3D
{

    class Cylinder : public BaseModel3D
    {
    private:

        float radius;
        float height;
        float sides;


    public:

        Cylinder(float radius, float height, Scene& _scene, float sides = 18, std::string tx_path = "../../assets/default/texture.tga");
        ~Cylinder();

        void createVertices(std::vector< GLfloat >& coordinates, std::vector< GLfloat >& normals, std::vector< GLfloat >& tx);
        void createIndices(std::vector< GLfloat >& coordinates);
        void createColors(std::vector< GLfloat >& colors, std::vector< GLfloat >& coodinates);

        void render() override;

        // Heredado vía BaseModel3D
        virtual void update() override;

    };

}

#endif
