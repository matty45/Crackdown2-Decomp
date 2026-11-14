// GangManager/cGangManager.cpp: RuffKing's Libraries/Shared/GangManager/cGangManager.cpp.
// The opening descriptor factory belongs to cGangInfo; CD2's split places it in this object.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "GangManager/cGangInfo.h"
#include "cd2/memory.h"

namespace GangManager
{
    Fun_Runtime::cClass &cGangInfo::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x40D, "cGangInfo", 0x1764);
        return *descriptor;
    }
}
