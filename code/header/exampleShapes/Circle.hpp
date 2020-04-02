
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CIRCLE_HEADER
#define CIRCLE_HEADER

#include "ExampleShape.hpp"

namespace exampleShapes
{

    class Circle : public ExampleShape
    {
    private:

        GLuint display_list_id;

    public:

        Circle(float radius)
        {
            create_display_list(radius);
        }

        ~Circle()
        {
            glDeleteLists(display_list_id, 1);
        }

        void render() override
        {
            glCallList(display_list_id);
        }

    private:

        void create_display_list(float radius)
        {
            // Se crea una lista y se guarda su identificador:

            display_list_id = glGenLists(1);

            // Se compilan los comandos que dibujan el círculo en la lista:

            glNewList(display_list_id, GL_COMPILE);
            {
                // Se dibuja el círculo con coordenadas locales de vértices cacheadas:

                glBegin(GL_TRIANGLE_FAN);
                {
                    // Se añade el primer vértice en el centro:

                    glVertex2f(0, 0);

                    // Se añaden vértices sobre el borde del círculo:

                    for (float angle = 0.f; angle < 6.283185f; angle += 0.05f)
                    {
                        glVertex2f(std::cosf(angle) * radius, std::sinf(angle) * radius);
                    }

                    // Se añade un último vértice de cierre donde angle vale 0

                    glVertex2f(radius, 0);
                }
                glEnd();
            }
            glEndList();
        }

    };

}

#endif
