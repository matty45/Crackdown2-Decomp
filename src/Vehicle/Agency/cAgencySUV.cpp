#include "rws/classfactory.h"
// src/Vehicle/Agency/cAgencySUV.cpp
//
// Class: cAgencySUV (namespace: Vehicle). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cAgencySUV.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Vehicle/Agency/cAgencySUV.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Vehicle/Agency/cAgencySUV.cpp

#include "Vehicle/cAgencySUV.h"
#include "cd2/memory.h"

namespace Vehicle
{
    const Fun_Runtime::cClass *cAgencySUV::ms_pcAgencySUVClass = &cAgencySUV::StaticCreateClass();

    Fun_Runtime::cClass &cAgencySUV::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgencySUVClass = new Fun_Runtime::cClass(0x12060, "cAgencySUV", 0x30C0);
        return *cAgencySUVClass;
    }
}

namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cAgencySUVRegistrar(
        "cAgencySUV", cAgencySUV::MakeNew, 0x30C0, false);
}

#include "fun_runtime/inheritance_registrar.h"
#include "Vehicle/cAgencyCar.h"

// CD2 0x82FEC170: runtime class inheritance registration.
namespace Vehicle
{
    static Fun_Runtime::cInheritanceRegistrar cAgencySUVcAgencyCarInheritRegistrar(
        Vehicle::cAgencySUV::StaticCreateClass(), Vehicle::cAgencyCar::StaticCreateClass());
}
