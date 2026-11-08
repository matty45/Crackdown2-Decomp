// RPG/cSkillSet.cpp: RuffKing's Libraries/Shared/RPG/cSkillSet.cpp.
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
#include "RPG/cSkillSet.h"
#include "cd2/memory.h"

namespace RPG
{
    Fun_Runtime::cClass &cSkillSet::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSkillSetClass = new Fun_Runtime::cClass(0x518, "cSkillSet", 0x64);
        return *cSkillSetClass;
    }

    const Fun_Runtime::cClass *cSkillSet::ms_pcSkillSetClass = &cSkillSet::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cSkillSetcDebugPageHandlerInheritRegistrar(
        cSkillSet::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());
}
