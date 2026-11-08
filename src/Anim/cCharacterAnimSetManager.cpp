// src/Anim/cCharacterAnimSetManager.cpp
//
// Class: cCharacterAnimSetManager (namespace: Anim). Set up automatically: no function is matched yet. The address
// range and the evidence for it are in config/splits.txt; RuffKing's object for it is cCharacterAnimSetManager.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Animation/cCharacterAnimSetManager.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Anim/cCharacterAnimSetManager.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "Anim/cCharacterAnimSetManager.h"
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"

namespace Anim
{
    const char *cCharacterAnimSetManager::RetClassName() const
    {
        return "cCharacterAnimSetManager";
    }

    Fun_Runtime::cClass &cCharacterAnimSetManager::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCharacterAnimSetManagerClass = new Fun_Runtime::cClass(0x5EC, "cCharacterAnimSetManager", 0x1400);
        return *cCharacterAnimSetManagerClass;
    }

    const Fun_Runtime::cClass *cCharacterAnimSetManager::ms_pcCharacterAnimSetManagerClass = &cCharacterAnimSetManager::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cCharacterAnimSetManagercNonGameBaseInheritRegistrar(
        cCharacterAnimSetManager::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cCharacterAnimSetManagerRegistrar(
        "cCharacterAnimSetManager", cCharacterAnimSetManager::MakeNew, 0x1400, false);

    const Fun_Runtime::cClass &cCharacterAnimSetManager::RetClass() const
    {
        return *ms_pcCharacterAnimSetManagerClass;
    }

    RWS::CAttributeHandler *cCharacterAnimSetManager::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCharacterAnimSetManager;
    }
}
