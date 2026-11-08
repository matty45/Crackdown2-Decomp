// VFX/cWeather.cpp: RuffKing's Libraries/Shared/VFX/cWeather.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

#include "fun_runtime/class.h"
#include "rws/classfactory.h"
#include "VFX/cWeatherSetup.h"
#include "VFX/cWeatherSystem.h"
#include "cd2/memory.h"

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cWeatherSetupRegistrar(
        "cWeatherSetup", cWeatherSetup::MakeNew, 0x64, false);

    static RWS::CClassFactory::CRegistrar cWeatherSystemRegistrar(
        "cWeatherSystem", cWeatherSystem::MakeNew, 0x3B0, false);
}
