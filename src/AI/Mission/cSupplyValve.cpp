#include "fun_runtime/retval.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cProp.h"
#include "rws/classfactory.h"
// src/AI/Mission/cSupplyValve.cpp
//
// Class: cSupplyValve (namespace: AI). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cSupplyValve.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/AI/Mission/cSupplyValve.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AI/Mission/cSupplyValve.cpp

#include "AI/cSupplyValve.h"

namespace AI
{
    const char *cSupplyValve::RetClassName() const
    {
        return "cSupplyValve";
    }
}

#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cSupplyValve::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSupplyValveClass = new Fun_Runtime::cClass(0x407, "cSupplyValve", 0xE50);
        return *cSupplyValveClass;
    }
}

namespace AI
{
    const Fun_Runtime::cClass *cSupplyValve::ms_pcSupplyValveClass = &cSupplyValve::StaticCreateClass();
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cSupplyValveRegistrar(
        "cSupplyValve", cSupplyValve::MakeNew, 0xE50, false);
}

// CD2 0x82F86618: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cSupplyValvecPropInheritRegistrar(
        AI::cSupplyValve::StaticCreateClass(), Prop::cProp::StaticCreateClass());
}

// CD2 0x82F866D0: register the class descriptor and placement factory.
namespace AI
{
    static GOM::cProtoRegistrar cSupplyValveSpawningRegistrar(
        cSupplyValve::StaticCreateClass(), cSupplyValve::SpawnFromPrototype);
}

namespace AI
{
    Fun_Runtime::RetVal cSupplyValve::cSupplyValvePrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
