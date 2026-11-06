// src/Equip/Weapon/cFlakCannon.cpp
//
// Class: cFlakCannon (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cFlakCannon.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cFlakCannon.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cFlakCannon.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Equip/cCWHeavyWeapon.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "Equip/cFlakCannon.h"
#include "cd2/memory.h"
#include <new>

namespace Equip
{
    const Fun_Runtime::cClass *cFlakCannon::ms_pcFlakCannonClass = &cFlakCannon::StaticCreateClass();

    RWS::CAttributeHandler *cFlakCannon::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cFlakCannon;
        return 0;
    }

    Fun_Runtime::cClass &cFlakCannon::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cFlakCannonClass = new Fun_Runtime::cClass(0x13269, "cFlakCannon", 0xA30);
        return *cFlakCannonClass;
    }

    static RWS::CClassFactory::CRegistrar cFlakCannonRegistrar(
        "cFlakCannon", cFlakCannon::MakeNew, 0xA30, false);

    // CD2 0x82FD4368: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cFlakCannonSpawningRegistrar(
        cFlakCannon::StaticCreateClass(), cFlakCannon::SpawnFromPrototype);

    // CD2 0x82FD42B0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cFlakCannoncCWHeavyWeaponInheritRegistrar(
        Equip::cFlakCannon::StaticCreateClass(), Equip::cCWHeavyWeapon::StaticCreateClass());

    RWS::CAttributeHandler *cFlakCannon::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cFlakCannonPrototype(packet);
    }

    const char *cFlakCannon::RetClassName() const
    {
        return "cFlakCannon";
    }

    // CD2 0x8263A940 has no derived cleanup beyond vtable restoration.
    cFlakCannon::~cFlakCannon()
    {
    }
}
