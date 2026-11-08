// PHYSICS::cStunt (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x827129E0, MakeNew 0x82711B38, from its registrars in CD2's
// initializer run); RuffKing names the class in cUniqueStuntZone.obj. No layout or virtuals are modelled yet.
#ifndef PHYSICS_CSTUNT_H
#define PHYSICS_CSTUNT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace PHYSICS
{
    class cStunt
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcStuntClass;
    };
}

#endif // PHYSICS_CSTUNT_H
