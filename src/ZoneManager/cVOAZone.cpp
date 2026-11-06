// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "ZoneManager/cVOAZone.h"
#include "cd2/memory.h"

namespace ZoneManager
{
    RWS::CAttributeHandler *cVOAZone::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cVOAZone(packet);
    }

    const char *cVOAZone::RetClassName() const
    {
        return "cVOAZone";
    }

    cVOAZone::~cVOAZone()
    {
    }

    static RWS::CClassFactory::CRegistrar cVOAZoneRegistrar(
        "cVOAZone", cVOAZone::MakeNew, 0x100, false);
}
