// src/PHYSICS/cPhysicsUniverse.cpp
//
// Class: cPhysicsUniverse (namespace: PHYSICS). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cPhysicsUniverse.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Physics/cPhysicsUniverse.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/PHYSICS/cPhysicsUniverse.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "GDb/cDebugPageHandler.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
#include "PHYSICS/cPhysicsUniverse.h"
#include "cd2/memory.h"

namespace PHYSICS
{
    const char *cPhysicsUniverse::RetClassName() const
    {
        return "cPhysicsUniverse";
    }

    Fun_Runtime::cClass &cPhysicsUniverse::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPhysicsUniverseClass = new Fun_Runtime::cClass(0x5FE, "cPhysicsUniverse", 0x80);
        return *cPhysicsUniverseClass;
    }

    const Fun_Runtime::cClass *cPhysicsUniverse::ms_pcPhysicsUniverseClass = &cPhysicsUniverse::StaticCreateClass();

    const Fun_Runtime::cClass &cPhysicsUniverse::RetClass() const
    {
        return *ms_pcPhysicsUniverseClass;
    }

    bool cPhysicsUniverse::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcPhysicsUniverseClass->IsA(c);
    }

    static RWS::CClassFactory::CRegistrar cPhysicsUniverseRegistrar(
        "cPhysicsUniverse", cPhysicsUniverse::MakeNew, 0x80, false);

    // CD2 0x82FE12D8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cPhysicsUniversecNonGameBaseInheritRegistrar(
        PHYSICS::cPhysicsUniverse::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    // CD2 0x82FE1340: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cPhysicsUniversecDebugPageHandlerInheritRegistrar(
        PHYSICS::cPhysicsUniverse::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());

    // CD2 0x8268DAA0: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cPhysicsUniverse::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cPhysicsUniverse;
    }
}
