// AI/Event/cSoundEvent.cpp: RuffKing's Libraries/Shared/AI/Event/cSoundEvent.cpp.
// Its text range and the evidence for it are in config/splits.txt; its own functions are not written yet.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cSoundEventSubscriptionTypeScriptRegistration.h"

namespace AI
{
    const char *cSoundEventSubscriptionTypeScriptRegistration::RetName() const
    {
        return "eSoundEventSubscriptionType";
    }

    // CD2 0x82F7A500 registers this four-byte enum object at 0x83818A58.
    static cSoundEventSubscriptionTypeScriptRegistration g_cSoundEventSubscriptionTypeScriptRegistration;
}
