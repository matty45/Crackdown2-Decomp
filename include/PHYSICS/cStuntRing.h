// PHYSICS::cStuntRing (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x82711C28, MakeNew 0x82711AD0, from its registrars in CD2's
// initializer run); RuffKing names the class in cUniqueStuntZone.obj. No layout or virtuals are modelled yet.
#ifndef PHYSICS_CSTUNTRING_H
#define PHYSICS_CSTUNTRING_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace PHYSICS
{
    class cStuntRing
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcStuntRingClass;
    };
}

#endif // PHYSICS_CSTUNTRING_H
