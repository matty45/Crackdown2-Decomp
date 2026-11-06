// src/Equip/Weapon/cHarpoonBolt.cpp
//
// Class: cHarpoonBolt (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cHarpoonBolt.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cHarpoonBolt.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cHarpoonBolt.cpp

#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Equip/cWeaponProjectile.h"
#include "rws/classfactory.h"
#include "Equip/cHarpoonBolt.h"
#include "cd2/memory.h"
#include <new>

namespace Equip
{
    RWS::CAttributeHandler *cHarpoonBolt::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cHarpoonBoltPrototype(packet);
    }

    const char *cHarpoonBolt::RetClassName() const
    {
        return "cHarpoonBolt";
    }

    Fun_Runtime::cClass &cHarpoonBolt::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cHarpoonBoltClass = new Fun_Runtime::cClass(0x42CB, "cHarpoonBolt", 0x910);
        return *cHarpoonBoltClass;
    }

    const Fun_Runtime::cClass *cHarpoonBolt::ms_pcHarpoonBoltClass = &cHarpoonBolt::StaticCreateClass();

    RWS::CAttributeHandler *cHarpoonBolt::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cHarpoonBolt;
        return 0;
    }

    static RWS::CClassFactory::CRegistrar cHarpoonBoltRegistrar(
        "cHarpoonBolt", cHarpoonBolt::MakeNew, 0x910, false);

    // CD2 0x82FD1E30: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cHarpoonBoltcWeaponProjectileInheritRegistrar(
        Equip::cHarpoonBolt::StaticCreateClass(), Equip::cWeaponProjectile::StaticCreateClass());

    // CD2 0x82FD1EE8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cHarpoonBoltSpawningRegistrar(
        cHarpoonBolt::StaticCreateClass(), cHarpoonBolt::SpawnFromPrototype);
}
