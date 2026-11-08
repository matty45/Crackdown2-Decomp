// VFX::cWeatherSystem (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x827D7AC8, from its registrars in CD2's
// initializer run); RuffKing names the class in cWeather.obj. No layout or virtuals are modelled yet.
#ifndef VFX_CWEATHERSYSTEM_H
#define VFX_CWEATHERSYSTEM_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace VFX
{
    class cWeatherSystem
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // VFX_CWEATHERSYSTEM_H
