// src/PHYSICS/cWaterZone.cpp
//
// Class: cWaterZone (namespace: PHYSICS). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cWaterZone.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Physics/cWaterZone.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/PHYSICS/cWaterZone.cpp

#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
#include "PHYSICS/cWaterZone.h"
#include "cd2/memory.h"

namespace PHYSICS
{
    const Fun_Runtime::cClass *cWaterZone::ms_pcWaterZoneClass = &cWaterZone::StaticCreateClass();

    Fun_Runtime::cClass &cWaterZone::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cWaterZoneClass = new Fun_Runtime::cClass(0x10F, "cWaterZone", 0x120);
        return *cWaterZoneClass;
    }

    static RWS::CClassFactory::CRegistrar cWaterZoneRegistrar(
        "cWaterZone", cWaterZone::MakeNew, 0x120, false);

    // CD2 0x82FEFBD0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cWaterZonecNonGameBaseInheritRegistrar(
        PHYSICS::cWaterZone::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    const char *cWaterZone::RetClassName() const
    {
        return "cWaterZone";
    }
}
