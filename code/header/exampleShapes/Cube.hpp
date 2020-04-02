
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CUBE_HEADER
#define CUBE_HEADER

#include "ExampleShape.hpp"

    namespace exampleShapes
    {

        class   Color_Buffer_Rgba8888;
        typedef Color_Buffer_Rgba8888 Texture;

        class Cube : public ExampleShape
        {
        private:

            static const GLfloat coordinates[][3];
            static const GLfloat normals    [][3];
            static const GLfloat tex_coords [][2];
            static const GLubyte indices    [][3];

        private:

            bool   has_texture;
            GLuint texture_id;

        public:

            Cube(const char * texture_path = 0);
           ~Cube();

        public:

            void render () override;

        private:

            std::auto_ptr< Texture > load_texture (const char * texture_file_path);

        };

    }

#endif
