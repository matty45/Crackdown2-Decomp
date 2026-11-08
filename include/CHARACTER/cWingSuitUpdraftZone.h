// CHARACTER::cWingSuitUpdraftZone (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x827284D8, from its registrars in CD2's
// initializer run); RuffKing names the class in cWingSuitUpdraftZone.obj. No layout or virtuals are modelled yet.
#ifndef CHARACTER_CWINGSUITUPDRAFTZONE_H
#define CHARACTER_CWINGSUITUPDRAFTZONE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace CHARACTER
{
    class cWingSuitUpdraftZone
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // CHARACTER_CWINGSUITUPDRAFTZONE_H
