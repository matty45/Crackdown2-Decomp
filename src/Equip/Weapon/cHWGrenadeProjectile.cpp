// src/Equip/Weapon/cHWGrenadeProjectile.cpp
//
// Class: cHWGrenadeProjectile (namespace: Equip). Set up automatically: no function is matched yet. The address range
// and the evidence for it are in config/splits.txt; RuffKing's object for it is cHWGrenadeProjectile.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cHWGrenadeProjectile.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cHWGrenadeProjectile.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Equip/cFlocket.h"
#include "rws/classfactory.h"
#include "Equip/cHWGrenadeProjectile.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"
#include <new>

namespace Equip
{
    const char *cHWGrenadeProjectile::RetClassName() const
    {
        return "cHWGrenadeProjectile";
    }

    Fun_Runtime::cClass &cHWGrenadeProjectile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cHWGrenadeProjectileClass = new Fun_Runtime::cClass(0x4275, "cHWGrenadeProjectile", 0xA40);
        return *cHWGrenadeProjectileClass;
    }

    const Fun_Runtime::cClass *cHWGrenadeProjectile::ms_pcHWGrenadeProjectileClass = &cHWGrenadeProjectile::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cHWGrenadeProjectileRegistrar(
        "cHWGrenadeProjectile", cHWGrenadeProjectile::MakeNew, 0xA40, false);

    // CD2 0x82FD2268: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cHWGrenadeProjectilecHWProjectileInheritRegistrar(
        Equip::cHWGrenadeProjectile::StaticCreateClass(), Equip::cHWProjectile::StaticCreateClass());

    // CD2 0x82FD2320: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cHWGrenadeProjectileSpawningRegistrar(
        cHWGrenadeProjectile::StaticCreateClass(), cHWGrenadeProjectile::SpawnFromPrototype);

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cHWGrenadeProjectile> cHWGrenadeProjectileScriptRegistrar(
        "cHWGrenadeProjectile", "cHWProjectile");

    RWS::CAttributeHandler *cHWGrenadeProjectile::SpawnFromPrototype(GOM::cObjectPrototype *pPrototype, void *pMem)
    {
        if (pMem)
            return new (pMem) cHWGrenadeProjectile(pPrototype);
        return 0;
    }

    const Fun_Runtime::cScriptTypeRegistration *cHWGrenadeProjectile::RetScriptTypeRegistration() const
    {
        return &cHWGrenadeProjectileScriptRegistrar;
    }
}
