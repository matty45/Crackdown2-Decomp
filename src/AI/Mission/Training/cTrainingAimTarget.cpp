// AI/Mission/Training/cTrainingAimTarget.cpp: RuffKing's Libraries/Shared/AI/Mission/Training/cTrainingAimTarget.cpp.
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
#include "rws/classfactory.h"
#include "AI/cTrainingAimTarget.h"
#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cTrainingAimTarget::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTrainingAimTargetClass = new Fun_Runtime::cClass(0x5D1F9, "cTrainingAimTarget", 0x160);
        return *cTrainingAimTargetClass;
    }

    const Fun_Runtime::cClass *cTrainingAimTarget::ms_pcTrainingAimTargetClass = &cTrainingAimTarget::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cTrainingAimTargetcAttachableLightInheritRegistrar(
        cTrainingAimTarget::StaticCreateClass(), cAttachableLight::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cTrainingAimTargetRegistrar(
        "cTrainingAimTarget", cTrainingAimTarget::MakeNew, 0x160, false);
}
