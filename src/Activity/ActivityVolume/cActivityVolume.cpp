// Activity/ActivityVolume/cActivityVolume.cpp: RuffKing's Libraries/Shared/ActivityManager/ActivityVolume/cActivityVolume.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/class.h"
#include "Activity/cActivityVolume.h"
#include "cd2/memory.h"

namespace Activity
{
    Fun_Runtime::cClass &cActivityVolume::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cActivityVolumeClass = new Fun_Runtime::cClass(0xD, "cActivityVolume", 0x90);
        return *cActivityVolumeClass;
    }

    const Fun_Runtime::cClass *cActivityVolume::ms_pcActivityVolumeClass = &cActivityVolume::StaticCreateClass();
}
