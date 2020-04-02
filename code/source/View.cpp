
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "../header/View.hpp"
#include <iostream>
#include <cassert>
#include "../header/Vertex_Shader.hpp"
#include "../header/Fragment_Shader.hpp"
#include "../header/exampleShapes/Cube.hpp"
#include "../header/exampleShapes/Sphere.hpp"

namespace exampleShapes
{

    using namespace std;

    View::View(int width, int height)
        :
        angle(0)
    {
        //Cubos
        /*shapes.push_back(new Cube("../../assets/tga/wood-crate-1.tga"));
        shapes.push_back(new Cube("../../assets/tga/wood-crate-2.tga"));*/

        //Esferas
        shapes.push_back(new Sphere(2,25,40));

        resize(width, height);

        glEnable(GL_CULL_FACE);

        // Se habilita el backface culling, una luz y materiales básicos:

        glEnable(GL_CULL_FACE);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);


        // Se compilan y se activan los shaders:

        shaderProgram.attach(Vertex_Shader(Shader::Source_Code::from_file("../../assets/vertexShader.vglsl")));
        shaderProgram.attach(Fragment_Shader(Shader::Source_Code::from_file("../../assets/fragmentShader.fglsl")));

        shaderProgram.link();
        shaderProgram.use();


    }

    void View::update(float time)
    {
        angle += 0.5f;

        static int light_direction = 1;
        static Vector3f ligh_position({-10,5,0});

        ligh_position[0] += 0.01f * light_direction;

        if (ligh_position[0] > 10)
            light_direction = -1;
        if(ligh_position[0] < -10)
            light_direction = 1;

        uploadUniformVariable("time", time);
        uploadUniformVariable("light_pos", ligh_position);
    }

    void View::render()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // Se establece la dirección de la luz:

       
        // Se inicializan los parámetros relativos a la iluminación:

        float light_direction[4] = { 0.1,0.1,1.0,0.0 };

        glLightfv(GL_LIGHT0, GL_POSITION, light_direction);

        float x = 0; // -2

        for (auto shape : shapes)
        {
            glLoadIdentity();
            glTranslatef(x, 0.f, -15.f); // - 10
            glRotatef(+angle, 1.f, 2.f, 1.f);

            shape->render();

            x += 4;
        }

    }

    void View::resize(int width, int height)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(20, GLdouble(width) / height, 1, 50);
        glViewport(0, 0, width, height);
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glMatrixMode(GL_MODELVIEW);
    }

    bool View::uploadUniformVariable(const char* name, float value)
    {
        GLint id = shaderProgram.get_uniform_id(name);

        if (id != -1)
        {
            shaderProgram.set_uniform_value(id, value);
            return true;

        }

        return false;
    }
    
    bool View::uploadUniformVariable(const char* name, Vector3f value)
    {
        GLint id = shaderProgram.get_uniform_id(name);

        if (id != -1)
        {
            shaderProgram.set_uniform_value(id, value);
            return true;

        }

        return false;
    }

}
