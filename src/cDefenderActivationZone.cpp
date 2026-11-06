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
