#include "rws/attributes.h"
// PHYSICS::cWaterZone (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82708208) builds cClass(0x10F, "cWaterZone", 0x120); 0x120 is the size its registrar gives.
#ifndef PHYSICS_CWATERZONE_H
#define PHYSICS_CWATERZONE_H

#include "fun_runtime/class.h"

namespace PHYSICS
{
    class cWaterZone
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcWaterZoneClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // PHYSICS_CWATERZONE_H
