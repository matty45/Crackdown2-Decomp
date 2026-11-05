// src/Vehicle/Agency/cAgencyBuggy.cpp
//
// Class: cAgencyBuggy (namespace: Vehicle). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cAgencyBuggy.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Vehicle/Agency/cAgencyBuggy.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Vehicle/Agency/cAgencyBuggy.cpp

#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "Vehicle/cAgencyBuggy.h"
#include "cd2/memory.h"
#include <new>
#include "Vehicle/cAgencyBuggyPrototype.h"

namespace Vehicle
{
    const Fun_Runtime::cClass *cAgencyBuggy::ms_pcAgencyBuggyClass = &cAgencyBuggy::StaticCreateClass();

    Fun_Runtime::cClass &cAgencyBuggy::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgencyBuggyClass = new Fun_Runtime::cClass(0x12064, "cAgencyBuggy", 0x30C0);
        return *cAgencyBuggyClass;
    }

    // CD2 0x82FEB0E0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAgencyBuggycAgencyCarInheritRegistrar(
        cAgencyBuggy::StaticCreateClass(), cAgencyCar::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cAgencyBuggyRegistrar(
        "cAgencyBuggy", cAgencyBuggy::MakeNew, 0x30C0, false);

    // CD2 0x82FEB198: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cAgencyBuggySpawningRegistrar(
        cAgencyBuggy::StaticCreateClass(), cAgencyBuggy::SpawnFromPrototype);

    const char *cAgencyBuggy::RetClassName() const
    {
        return "cAgencyBuggy";
    }

    RWS::CAttributeHandler *cAgencyBuggy::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cAgencyBuggy;
        return 0;
    }

    Fun_Runtime::RetVal cAgencyBuggyPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
