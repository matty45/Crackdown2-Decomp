// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cMissionActivationZone.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cMissionActivationZone::RetClassName() const
    {
        return "cMissionActivationZone";
    }

    // CD2 0x8248B510: only the member's and the bases' destruction.
    cMissionActivationZone::~cMissionActivationZone()
    {
    }

    static RWS::CClassFactory::CRegistrar cMissionActivationZoneRegistrar(
        "cMissionActivationZone", cMissionActivationZone::MakeNew, 0x100, false);
}
