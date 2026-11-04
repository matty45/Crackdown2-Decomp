// src/Vehicle/Agency/cAgencyCar.cpp
//
// Class: cAgencyCar (namespace: Vehicle). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cAgencyCar.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Vehicle/Agency/cAgencyCar.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Vehicle/Agency/cAgencyCar.cpp

#include "rws/classfactory.h"
#include "Vehicle/cAgencyCar.h"

// CD2 0x826EC178.
namespace Vehicle
{
    const char *cAgencyCar::RetClassName() const
    {
        return "cAgencyCar";
    }
}

// CD2 0x82FEB4F8 (initializer) and 0x83040A50 (at-exit destructor).
namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cAgencyCarRegistrar(
        "cAgencyCar", cAgencyCar::MakeNew, 0x30B0, false);
}
