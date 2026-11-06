// src/Equip/Weapon/cClusterGrenade.cpp
//
// Class: cClusterGrenade (namespace: Equip). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cClusterGrenade.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cClusterGrenade.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cClusterGrenade.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "fun_runtime/retval.h"
#include "Equip/cExplosiveGrenade.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "Equip/cClusterGrenade.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cClusterGrenade::ms_pcClusterGrenadeClass = &cClusterGrenade::StaticCreateClass();

    Fun_Runtime::cClass &cClusterGrenade::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cClusterGrenadeClass = new Fun_Runtime::cClass(0x3E8E, "cClusterGrenade", 0x9D0);
        return *cClusterGrenadeClass;
    }

    static RWS::CClassFactory::CRegistrar cClusterGrenadeRegistrar(
        "cClusterGrenade", cClusterGrenade::MakeNew, 0x9D0, false);

    // CD2 0x82FCF230: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cClusterGrenadeSpawningRegistrar(
        cClusterGrenade::StaticCreateClass(), cClusterGrenade::SpawnFromPrototype);

    // CD2 0x82FCF178: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cClusterGrenadecExplosiveGrenadeInheritRegistrar(
        Equip::cClusterGrenade::StaticCreateClass(), Equip::cExplosiveGrenade::StaticCreateClass());

    const char *cClusterGrenade::RetClassName() const
    {
        return "cClusterGrenade";
    }

    RWS::CAttributeHandler *cClusterGrenade::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cClusterGrenade;
        return 0;
    }

    Fun_Runtime::RetVal cClusterGrenade::cClusterGrenadePrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
