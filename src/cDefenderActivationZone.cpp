// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "unknown/cDefenderActivationZone.h"
#include "rws/classfactory.h"

namespace unknown
{
    const char *cDefenderActivationZone::RetClassName() const
    {
        return "cDefenderActivationZone";
    }

    static RWS::CClassFactory::CRegistrar cDefenderActivationZoneRegistrar(
        "cDefenderActivationZone", cDefenderActivationZone::MakeNew, 0x100, false);
}
