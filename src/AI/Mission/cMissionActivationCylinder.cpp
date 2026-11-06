#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cMissionActivationCylinder.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cMissionActivationCylinder::RetClassName() const
    {
        return "cMissionActivationCylinder";
    }

    // CD2 0x8248B058: only the member's and the bases' destruction.
    cMissionActivationCylinder::~cMissionActivationCylinder()
    {
    }

    static RWS::CClassFactory::CRegistrar cMissionActivationCylinderRegistrar(
        "cMissionActivationCylinder", cMissionActivationCylinder::MakeNew, 0x110, false);
}
