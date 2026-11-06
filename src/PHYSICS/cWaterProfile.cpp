// src/PHYSICS/cWaterProfile.cpp
//
// Class: cWaterProfile (namespace: PHYSICS). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cWaterProfile.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Physics/cWaterProfile.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/PHYSICS/cWaterProfile.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "GDb/cDebugPageHandler.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
#include "PHYSICS/cWaterProfile.h"
#include "cd2/memory.h"

namespace PHYSICS
{
    const char *cWaterProfile::RetClassName() const
    {
        return "cWaterProfile";
    }

    Fun_Runtime::cClass &cWaterProfile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cWaterProfileClass = new Fun_Runtime::cClass(0x5FF, "cWaterProfile", 0x7C);
        return *cWaterProfileClass;
    }

    const Fun_Runtime::cClass *cWaterProfile::ms_pcWaterProfileClass = &cWaterProfile::StaticCreateClass();

    const Fun_Runtime::cClass &cWaterProfile::RetClass() const
    {
        return *ms_pcWaterProfileClass;
    }

    bool cWaterProfile::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcWaterProfileClass->IsA(c);
    }

    static RWS::CClassFactory::CRegistrar cWaterProfileRegistrar(
        "cWaterProfile", cWaterProfile::MakeNew, 0x7C, false);

    // CD2 0x82FE2670: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cWaterProfilecNonGameBaseInheritRegistrar(
        PHYSICS::cWaterProfile::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    // CD2 0x82FE26D8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cWaterProfilecDebugPageHandlerInheritRegistrar(
        PHYSICS::cWaterProfile::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());
}
