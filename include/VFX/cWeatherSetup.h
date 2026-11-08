// VFX::cWeatherSetup (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x827D7A08, from its registrars in CD2's
// initializer run); RuffKing names the class in cWeather.obj. No layout or virtuals are modelled yet.
#ifndef VFX_CWEATHERSETUP_H
#define VFX_CWEATHERSETUP_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace VFX
{
    class cWeatherSetup
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // VFX_CWEATHERSETUP_H
