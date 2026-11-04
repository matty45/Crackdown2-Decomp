#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
// src/Vehicle/Agency/cAgencySports.cpp
//
// Class: cAgencySports (namespace: Vehicle). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cAgencySports.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Vehicle/Agency/cAgencySports.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Vehicle/Agency/cAgencySports.cpp

#include "Vehicle/cAgencySports.h"
#include "cd2/memory.h"

namespace Vehicle
{
    const Fun_Runtime::cClass *cAgencySports::ms_pcAgencySportsClass = &cAgencySports::StaticCreateClass();

    Fun_Runtime::cClass &cAgencySports::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgencySportsClass = new Fun_Runtime::cClass(0x12061, "cAgencySports", 0x30C0);
        return *cAgencySportsClass;
    }
}

namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cAgencySportsRegistrar(
        "cAgencySports", cAgencySports::MakeNew, 0x30C0, false);
}

// CD2 0x82FEB980: register the class descriptor and placement factory.
namespace Vehicle
{
    static GOM::cProtoRegistrar cAgencySportsSpawningRegistrar(
        cAgencySports::StaticCreateClass(), cAgencySports::SpawnFromPrototype);
}

namespace Vehicle
{
    const char *cAgencySports::RetClassName() const
    {
        return "cAgencySports";
    }
}

namespace Vehicle
{
    const Fun_Runtime::cClass &cAgencySports::RetClass() const
    {
        return *ms_pcAgencySportsClass;
    }
}

#include "Vehicle/cAgencySportsPrototype.h"

namespace Vehicle
{
    Fun_Runtime::RetVal cAgencySportsPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
