// AI/Targeting/cAiTargetPositionInfo.cpp: RuffKing's Libraries/Shared/Ai/Targeting/cAiTargetPositionInfo.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cAiTargetPositionInfo.h"
#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cAiTargetPositionInfo::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAiTargetPositionInfoClass = new Fun_Runtime::cClass(0x411, "cAiTargetPositionInfo", 0x210);
        return *cAiTargetPositionInfoClass;
    }

    const Fun_Runtime::cClass *cAiTargetPositionInfo::ms_pcAiTargetPositionInfoClass = &cAiTargetPositionInfo::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cAiTargetPositionInfocAiTargetInfoInheritRegistrar(
        cAiTargetPositionInfo::StaticCreateClass(), cAiTargetInfo::StaticCreateClass());
}
