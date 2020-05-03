
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
        static std::string camera_shader_path;
        static std::string skybox_shader_path;
        static std::string postprocesing_shader_path;
        static std::string vertexShader_name;
        static std::string fragmentShader_name;
        static std::string shader_camera_matrix;
        static std::string shader_model_matrix ;
        static std::string shader_camera_position;

    };

}
#endif
