// src/Equip/Weapon/cHWProjectile.cpp
//
// Class: cHWProjectile (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cHWProjectile.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cHWProjectile.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cHWProjectile.cpp

// CD2 0x82FD26F8: runtime class inheritance registration.

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "cd2/memory.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Equip/cFlocket.h"
#include "Equip/cWeaponProjectile.h"
#include "rws/classfactory.h"

namespace Equip
{
    Fun_Runtime::cClass &cHWProjectile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cHWProjectileClass = new Fun_Runtime::cClass(17002, "cHWProjectile", 0x970);
        return *cHWProjectileClass;
    }

    const Fun_Runtime::cClass *cHWProjectile::ms_pcHWProjectileClass = &cHWProjectile::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cHWProjectilecWeaponProjectileInheritRegistrar(
        Equip::cHWProjectile::StaticCreateClass(), Equip::cWeaponProjectile::StaticCreateClass());

    // CD2 0x82FD2760: register the class factory.
    static RWS::CClassFactory::CRegistrar cHWProjectileRegistrar(
        "cHWProjectile", cHWProjectile::MakeNew, 0x970, false);

    // CD2 0x82FD27B0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cHWProjectileSpawningRegistrar(
        cHWProjectile::StaticCreateClass(), cHWProjectile::SpawnFromPrototype);

    const char *cHWProjectile::RetClassName() const
    {
        return "cHWProjectile";
    }

    RWS::CAttributeHandler *cHWProjectile::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cHWProjectile;
        return 0;
    }
}
