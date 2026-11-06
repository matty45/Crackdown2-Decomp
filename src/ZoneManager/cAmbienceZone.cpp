#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "ZoneManager/cAmbienceZone.h"
#include "cd2/memory.h"

namespace ZoneManager
{
    RWS::CAttributeHandler *cAmbienceZone::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAmbienceZone(packet);
    }

    const char *cAmbienceZone::RetClassName() const
    {
        return "cAmbienceZone";
    }

    cAmbienceZone::~cAmbienceZone()
    {
    }

    static RWS::CClassFactory::CRegistrar cAmbienceZoneRegistrar(
        "cAmbienceZone", cAmbienceZone::MakeNew, 0x100, false);
}
