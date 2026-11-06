#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cMissionCompletionZone.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cMissionCompletionZone::RetClassName() const
    {
        return "cMissionCompletionZone";
    }

    static RWS::CClassFactory::CRegistrar cMissionCompletionZoneRegistrar(
        "cMissionCompletionZone", cMissionCompletionZone::MakeNew, 0xF0, false);
}
