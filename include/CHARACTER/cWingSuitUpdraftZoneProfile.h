// CHARACTER::cWingSuitUpdraftZoneProfile (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x82728400, from its registrars in CD2's
// initializer run); RuffKing names the class in cWingSuitUpdraftZone.obj. No layout or virtuals are modelled yet.
#ifndef CHARACTER_CWINGSUITUPDRAFTZONEPROFILE_H
#define CHARACTER_CWINGSUITUPDRAFTZONEPROFILE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace CHARACTER
{
    class cWingSuitUpdraftZoneProfile
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // CHARACTER_CWINGSUITUPDRAFTZONEPROFILE_H
