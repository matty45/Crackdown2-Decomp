// src/Equip/Weapon/cCWSatchelCharge.cpp
//
// Class: cCWSatchelCharge (namespace: Equip). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cCWSatchelCharge.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cCWSatchelCharge.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cCWSatchelCharge.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "Equip/cCWSatchelCharge.h"
#include "fun_runtime/script_type_registrar.h"
#include "cd2/memory.h"
#include <new>
#include "rws/classfactory.h"

namespace Equip
{
    bool cCWSatchelCharge::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcCWSatchelChargeClass->IsA(c);
    }

    RWS::CAttributeHandler *cCWSatchelCharge::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCWSatchelChargePrototype(packet);
    }

    const char *cCWSatchelCharge::RetClassName() const
    {
        return "cCWSatchelCharge";
    }

    // CD2 0x82FCF618: register the class factory.
    static RWS::CClassFactory::CRegistrar cCWSatchelChargeRegistrar(
        "cCWSatchelCharge", cCWSatchelCharge::MakeNew, 0xAE0, false);

    // CD2 script-type registration names this child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cCWSatchelCharge> cCWSatchelChargeScriptRegistrar(
        "cCWSatchelCharge", "cExplosiveGrenade");

    RWS::CAttributeHandler *cCWSatchelCharge::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cCWSatchelCharge;
        return 0;
    }

    Fun_Runtime::cClass &cCWSatchelCharge::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x3E97, "cCWSatchelCharge", 0xAE0);
        return *descriptor;
    }

    const Fun_Runtime::cClass *cCWSatchelCharge::ms_pcCWSatchelChargeClass = &cCWSatchelCharge::StaticCreateClass();

    const Fun_Runtime::cClass &cCWSatchelCharge::RetClass() const
    {
        return *ms_pcCWSatchelChargeClass;
    }
}
