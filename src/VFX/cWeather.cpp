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
    RWS::CAttributeHandler *cWeatherSetup::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cWeatherSetup(packet);
    }

    const char *cWeatherSetup::RetClassName() const
    {
        return "cWeatherSetup";
    }

    RWS::CAttributeHandler *cWeatherSystem::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cWeatherSystem;
    }

    const char *cWeatherSystem::RetClassName() const
    {
        return "cWeatherSystem";
    }

    static RWS::CClassFactory::CRegistrar cWeatherSetupRegistrar(
        "cWeatherSetup", cWeatherSetup::MakeNew, 0x64, false);

    static RWS::CClassFactory::CRegistrar cWeatherSystemRegistrar(
        "cWeatherSystem", cWeatherSystem::MakeNew, 0x3B0, false);
}
