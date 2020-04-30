
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge Barcena on March of 2020                                  *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SPHERE_HEADER
#define SPHERE_HEADER

#include <vector>
#include "BaseShape.hpp"

namespace exampleShapes
{

    class Sphere : public BaseShape
    {

    private:

    

        // Características de la aproximación a la esfera:

        struct Features
        {
            float radius;
            int   number_of_bands;      // Numéro de bandas paralelas al ecuador
            int   number_of_slices;     // Número de secciones de polo a polo
        };

        // Coordenadas de un punto o de un vector:

        struct Coordinates
        {
            enum
            {
                X, Y, Z
            };

            GLfloat values[3];

            Coordinates()
            {
            }

            Coordinates(GLfloat x, GLfloat y, GLfloat z)
            {
                values[X] = x;
                values[Y] = y;
                values[Z] = z;
            }
        };


    private:

        Features           features;    // Características de la aproximación a la esfera
    public:

        Sphere(float radius, int number_of_bands = 10, int number_of_slices = 20);

        void render() override;

    private:

        void cache_geometry();
        void cache_point(const float alpha, const float beta);
        void cache_ring(const float beta);
        void cache_normals();
        void weave_cap(int tip_index, int ring_start_index, int step);
        void weave_band(int band_a_start_index, int band_b_start_index);

    };

}

#endif
