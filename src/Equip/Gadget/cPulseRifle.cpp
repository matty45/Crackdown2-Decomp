// src/Equip/Gadget/cPulseRifle.cpp
//
// Class: cPulseRifle (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cPulseRifle.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Gadget/cPulseRifle.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Gadget/cPulseRifle.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/retval.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Equip/cCWWeapon.h"
#include "rws/classfactory.h"
#include "Equip/cPulseRifle.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cPulseRifle::ms_pcPulseRifleClass = &cPulseRifle::StaticCreateClass();

    Fun_Runtime::cClass &cPulseRifle::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPulseRifleClass = new Fun_Runtime::cClass(0x27413, "cPulseRifle", 0xA80);
        return *cPulseRifleClass;
    }

    static RWS::CClassFactory::CRegistrar cPulseRifleRegistrar(
        "cPulseRifle", cPulseRifle::MakeNew, 0xA80, false);

    // CD2 0x82FCD220: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cPulseRiflecCWWeaponInheritRegistrar(
        Equip::cPulseRifle::StaticCreateClass(), Equip::cCWWeapon::StaticCreateClass());

    // CD2 0x82FCD2D8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cPulseRifleSpawningRegistrar(
        cPulseRifle::StaticCreateClass(), cPulseRifle::SpawnFromPrototype);

    RWS::CAttributeHandler *cPulseRifle::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cPulseRiflePrototype(packet);
    }

    const char *cPulseRifle::RetClassName() const
    {
        return "cPulseRifle";
    }

    Fun_Runtime::RetVal cPulseRifle::cPulseRiflePrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
