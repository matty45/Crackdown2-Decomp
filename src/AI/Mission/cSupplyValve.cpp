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

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "fun_runtime/retval.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cProp.h"
#include "rws/classfactory.h"
#include "AI/cSupplyValve.h"
#include "cd2/memory.h"

namespace AI
{
    RWS::CAttributeHandler *cSupplyValve::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cSupplyValvePrototype(packet);
    }

    const char *cSupplyValve::RetClassName() const
    {
        return "cSupplyValve";
    }

    // CD2 0x822C8900 has no derived cleanup beyond vtable restoration.
    cSupplyValve::~cSupplyValve()
    {
    }

    Fun_Runtime::cClass &cSupplyValve::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSupplyValveClass = new Fun_Runtime::cClass(0x407, "cSupplyValve", 0xE50);
        return *cSupplyValveClass;
    }

    const Fun_Runtime::cClass *cSupplyValve::ms_pcSupplyValveClass = &cSupplyValve::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cSupplyValveRegistrar(
        "cSupplyValve", cSupplyValve::MakeNew, 0xE50, false);

    // CD2 0x82F86618: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cSupplyValvecPropInheritRegistrar(
        AI::cSupplyValve::StaticCreateClass(), Prop::cProp::StaticCreateClass());

    // CD2 0x82F866D0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cSupplyValveSpawningRegistrar(
        cSupplyValve::StaticCreateClass(), cSupplyValve::SpawnFromPrototype);

    Fun_Runtime::RetVal cSupplyValve::cSupplyValvePrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
