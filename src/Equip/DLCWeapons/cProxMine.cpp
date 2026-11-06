// src/Equip/DLCWeapons/cProxMine.cpp
//
// Class: cProxMine (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cProxMine.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/DLCWeapons/cProxMine.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/DLCWeapons/cProxMine.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/retval.h"
#include "Equip/cCWSatchelCharge.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "Equip/cProxMine.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cProxMine::ms_pcProxMineClass = &cProxMine::StaticCreateClass();

    Fun_Runtime::cClass &cProxMine::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cProxMineClass = new Fun_Runtime::cClass(0x13265, "cProxMine", 0xB10);
        return *cProxMineClass;
    }

    static RWS::CClassFactory::CRegistrar cProxMineRegistrar(
        "cProxMine", cProxMine::MakeNew, 0xB10, false);

    // CD2 0x82FD0470: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cProxMineSpawningRegistrar(
        cProxMine::StaticCreateClass(), cProxMine::SpawnFromPrototype);

    // CD2 0x82FD03B8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cProxMinecCWSatchelChargeInheritRegistrar(
        Equip::cProxMine::StaticCreateClass(), Equip::cCWSatchelCharge::StaticCreateClass());

    RWS::CAttributeHandler *cProxMine::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cProxMinePrototype(packet);
    }

    const char *cProxMine::RetClassName() const
    {
        return "cProxMine";
    }

    const Fun_Runtime::cClass &cProxMine::RetClass() const
    {
        return *ms_pcProxMineClass;
    }

    bool cProxMine::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcProxMineClass->IsA(c);
    }

    // CD2 0x8261FB48 has no derived cleanup beyond vtable restoration.
    cProxMine::~cProxMine()
    {
    }

    RWS::CAttributeHandler *cProxMine::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cProxMine;
        return 0;
    }

    Fun_Runtime::RetVal cProxMine::cProxMinePrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
