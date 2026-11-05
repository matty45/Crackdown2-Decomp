// src/AI/Mission/cAmbientEventMission.cpp
//
// Class: cAmbientEventMission (namespace: AI). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cAmbientEventMission.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/AI/Mission/cAmbientEventMission.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AI/Mission/cAmbientEventMission.cpp

#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "AI/cAmbientEventMission.h"
#include "cd2/memory.h"

namespace AI
{
    const char *cAmbientEventMission::RetClassName() const
    {
        return "cAmbientEventMission";
    }

    const Fun_Runtime::cClass *cAmbientEventMission::ms_pcAmbientEventMissionClass = &cAmbientEventMission::StaticCreateClass();

    Fun_Runtime::cClass &cAmbientEventMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAmbientEventMissionClass = new Fun_Runtime::cClass(0x9FE8B, "cAmbientEventMission", 0x3B0);
        return *cAmbientEventMissionClass;
    }

    static RWS::CClassFactory::CRegistrar cAmbientEventMissionRegistrar(
        "cAmbientEventMission", cAmbientEventMission::MakeNew, 0x3B0, false);

    // CD2 0x82F900E0: runtime mission inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAmbientEventMissioncMissionBaseInheritRegistrar(
        AI::cAmbientEventMission::StaticCreateClass(), AI::cMissionBase::StaticCreateClass());
}
