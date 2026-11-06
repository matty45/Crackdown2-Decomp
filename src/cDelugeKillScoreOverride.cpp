#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "unknown/cDelugeKillScoreOverride.h"
#include "rws/classfactory.h"

namespace unknown
{
    const char *cDelugeKillScoreOverride::RetClassName() const
    {
        return "cDelugeKillScoreOverride";
    }

    RWS::CAttributeHandler *cDelugeKillScoreOverride::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cDelugeKillScoreOverride *p = new cDelugeKillScoreOverride();
        return p;
    }

    static RWS::CClassFactory::CRegistrar cDelugeKillScoreOverrideRegistrar(
        "cDelugeKillScoreOverride", cDelugeKillScoreOverride::MakeNew, 0x18, false);
}
