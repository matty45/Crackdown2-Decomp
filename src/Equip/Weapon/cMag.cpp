// src/Equip/Weapon/cMag.cpp
//
// Class: cMag (namespace: Equip). Set up automatically: no function is matched yet. The address range and the evidence
// for it are in config/splits.txt; RuffKing's object for it is cMag.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cMag.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cMag.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
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
#include "Equip/cMag.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cMag::ms_pcMagClass = &cMag::StaticCreateClass();

    Fun_Runtime::cClass &cMag::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cMagClass = new Fun_Runtime::cClass(0x27411, "cMag", 0xB20);
        return *cMagClass;
    }

    static RWS::CClassFactory::CRegistrar cMagRegistrar(
        "cMag", cMag::MakeNew, 0xB20, false);

    // CD2 0x82FCCC00: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cMagSpawningRegistrar(
        cMag::StaticCreateClass(), cMag::SpawnFromPrototype);

    // CD2 0x82FCCB48: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cMagcCWSatchelChargeInheritRegistrar(
        Equip::cMag::StaticCreateClass(), Equip::cCWSatchelCharge::StaticCreateClass());

    const char *cMag::RetClassName() const
    {
        return "cMag";
    }

    RWS::CAttributeHandler *cMag::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cMag;
        return 0;
    }

    Fun_Runtime::RetVal cMag::cMagPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
