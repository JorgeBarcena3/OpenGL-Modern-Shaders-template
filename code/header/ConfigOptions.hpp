// File: ConfigOptions.hpp
// Author: Jorge Bárcena Lumbreras

// © Copyright (C) 2020  Jorge Bárcena Lumbreras

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>

#define GLM_FORCE_RADIANS

#ifndef CONFIGOPTIONS_HEADER
#define CONFIGOPTIONS_HEADER

#include <string>

namespace ConfigOptions
{

    /**
    * Guarda la informacion de los paths para la aplicacion
    */
    class ConfigPaths
    {
    public:

        static std::map<std::string, std::string> configSettingsMap; ///< Mapa que guarda el nombre de la congiguracion y el path al que está asociado

    };

}
#endif
