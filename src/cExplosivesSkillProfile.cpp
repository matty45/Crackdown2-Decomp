// src/cExplosivesSkillProfile.cpp
//
// Class: cExplosivesSkillProfile (namespace: RPG). Set up automatically: no function is matched yet. The address
// range and the evidence for it are in config/splits.txt; RuffKing's object for it is cExplosivesSkillProfile.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/RPG/cExplosivesSkillProfile.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cExplosivesSkillProfile.cpp


// CD2 0x82753190.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "rws/classfactory.h"
#include "RPG/cExplosivesSkillProfile.h"
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"

namespace RPG
{
    const char *cExplosivesSkillProfile::RetClassName() const
    {
        return "cExplosivesSkillProfile";
    }

    // CD2 0x82FFD408 (initializer) and 0x83041D40 (at-exit destructor).
    Fun_Runtime::cClass &cExplosivesSkillProfile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cExplosivesSkillProfileClass = new Fun_Runtime::cClass(0x607, "cExplosivesSkillProfile", 0xA4);
        return *cExplosivesSkillProfileClass;
    }

    const Fun_Runtime::cClass *cExplosivesSkillProfile::ms_pcExplosivesSkillProfileClass = &cExplosivesSkillProfile::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cExplosivesSkillProfilecNonGameBaseInheritRegistrar(
        cExplosivesSkillProfile::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cExplosivesSkillProfileRegistrar(
        "cExplosivesSkillProfile", cExplosivesSkillProfile::MakeNew, 0xA4, false);
}
