#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "ZoneManager/cReverbZone.h"
#include "cd2/memory.h"

namespace ZoneManager
{
    RWS::CAttributeHandler *cReverbZone::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cReverbZone(packet);
    }

    const char *cReverbZone::RetClassName() const
    {
        return "cReverbZone";
    }

    cReverbZone::~cReverbZone()
    {
    }

    static RWS::CClassFactory::CRegistrar cReverbZoneRegistrar(
        "cReverbZone", cReverbZone::MakeNew, 0x150, false);
}
