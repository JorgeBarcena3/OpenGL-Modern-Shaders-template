
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

        static std::map<std::string, std::string> configSettingsMap;

    };

}
#endif
