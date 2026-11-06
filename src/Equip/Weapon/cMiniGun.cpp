// src/Equip/Weapon/cMiniGun.cpp
//
// Class: cMiniGun (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cMiniGun.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cMiniGun.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cMiniGun.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Equip/cCWFirearm.h"
#include "rws/classfactory.h"
#include "Equip/cMiniGun.h"
#include "cd2/memory.h"
#include <new>

namespace Equip
{
    const Fun_Runtime::cClass *cMiniGun::ms_pcMiniGunClass = &cMiniGun::StaticCreateClass();

    RWS::CAttributeHandler *cMiniGun::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cMiniGun;
        return 0;
    }

    Fun_Runtime::cClass &cMiniGun::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cMiniGunClass = new Fun_Runtime::cClass(0x13268, "cMiniGun", 0xAC0);
        return *cMiniGunClass;
    }

    static RWS::CClassFactory::CRegistrar cMiniGunRegistrar(
        "cMiniGun", cMiniGun::MakeNew, 0xAC0, false);

    // CD2 0x82FD4660: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cMiniGuncCWFirearmInheritRegistrar(
        Equip::cMiniGun::StaticCreateClass(), Equip::cCWFirearm::StaticCreateClass());

    // CD2 0x82FD4718: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cMiniGunSpawningRegistrar(
        cMiniGun::StaticCreateClass(), cMiniGun::SpawnFromPrototype);

    const char *cMiniGun::RetClassName() const
    {
        return "cMiniGun";
    }

    // CD2 0x8263B410 has no derived cleanup beyond vtable restoration.
    cMiniGun::~cMiniGun()
    {
    }
}
