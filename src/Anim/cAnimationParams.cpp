// Anim/cAnimationParams.cpp: RuffKing's Libraries/Shared/Animation/cAnimationParams.cpp.
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
#include "fun_runtime/inheritance_registrar.h"
#include "Anim/cAnimationParams.h"
#include "cd2/memory.h"

namespace Anim
{
    Fun_Runtime::cClass &cAnimationParams::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAnimationParamsClass = new Fun_Runtime::cClass(0x3F4, "cAnimationParams", 0x30);
        return *cAnimationParamsClass;
    }

    const Fun_Runtime::cClass *cAnimationParams::ms_pcAnimationParamsClass = &cAnimationParams::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cAnimationParamscScriptHostInheritRegistrar(
        cAnimationParams::StaticCreateClass(), Fun_Runtime::cScriptHost::StaticCreateClass());
}
