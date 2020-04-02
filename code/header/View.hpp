
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef VIEW_HEADER
#define VIEW_HEADER

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "exampleShapes/ExampleShape.hpp"
#include <string>
#include "Shader_Program.hpp"

namespace exampleShapes
{

    using namespace shaderToolkit;

    class View
    {
    private:

        static const std::string   vertex_shader_code;
        static const std::string fragment_shader_code;

        std::vector< ExampleShape * > shapes;
        float  angle;

    public:

        View(int width, int height);

        void   update(float time);
        void   render();
        void   resize(int width, int height);
        bool   uploadUniformVariable(const char * name, float value);
        bool   uploadUniformVariable(const char* name, Vector3f value);

    private:

        Shader_Program shaderProgram;
    };

}

#endif
