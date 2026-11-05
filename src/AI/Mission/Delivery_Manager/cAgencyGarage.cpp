// src/AI/Mission/Delivery_Manager/cAgencyGarage.cpp
//
// Class: cAgencyGarage (namespace: AI). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cAgencyGarage.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/AI/Mission/Delivery_Manager/cAgencyGarage.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AI/Mission/Delivery_Manager/cAgencyGarage.cpp


// CD2 0x82479BC8.

#include "rws/classfactory.h"
#include "AI/cAgencyGarage.h"

namespace AI
{
    const char *cAgencyGarage::RetClassName() const
    {
        return "cAgencyGarage";
    }

    // CD2 0x82F8B1E8 (initializer) and 0x8303B100 (at-exit destructor).
    static RWS::CClassFactory::CRegistrar cAgencyGarageRegistrar(
        "cAgencyGarage", cAgencyGarage::MakeNew, 0x380, false);
}
