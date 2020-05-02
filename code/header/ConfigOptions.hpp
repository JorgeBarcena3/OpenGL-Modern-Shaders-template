
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define GLM_FORCE_RADIANS

#ifndef CONFIGOPTIONS_HEADER
#define CONFIGOPTIONS_HEADER

#include <string>

namespace ConfigOptions
{

    class ConfigPaths
    {
    public:

        static std::string texture_default_path;
        static std::string shader_myMaterialKa;
        static std::string shader_myMaterialKd;
        static std::string shader_myMaterialKs;
        static std::string shader_pointLight_array;
        static std::string shader_directionalLight_array;
    };

}
#endif
