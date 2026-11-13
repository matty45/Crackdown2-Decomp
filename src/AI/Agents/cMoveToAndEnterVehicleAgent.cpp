// Partial cMoveToAndEnterVehicleAgent object: eDoorSelection's seven names and values agree
// with RuffKing's cMoveToAndEnterVehicleAgent.h. CD2 table 0x820FD9D8 identifies its enum;
// initializer 0x82F6A8F8 installs it after this object's complete header-constant run.
// The agent's own implementation remains open; no instance layout is inferred here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "AI/aiconstants.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/cDoorSelectionScriptRegistration.h"

namespace AI
{
    const char *cDoorSelectionScriptRegistration::RetName() const
    {
        return "eDoorSelection";
    }

    // CD2 0x82F6A8F8 registers this four-byte enum object at 0x83814528.
    static cDoorSelectionScriptRegistration g_cDoorSelectionScriptRegistration;
}
