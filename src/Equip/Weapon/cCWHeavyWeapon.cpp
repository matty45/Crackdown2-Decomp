// src/Equip/Weapon/cCWHeavyWeapon.cpp
//
// Class: cCWHeavyWeapon (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cCWHeavyWeapon.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cCWHeavyWeapon.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cCWHeavyWeapon.cpp

// CD2 0x82FD2FA8: class descriptor and placement factory.

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "cd2/memory.h"
#include "Equip/cCWHeavyWeapon.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/script_type_registrar.h"
#include "rws/classfactory.h"

namespace Equip
{
    // CD2 0x82FD2F58: register the class factory.
    static RWS::CClassFactory::CRegistrar cCWHeavyWeaponRegistrar(
        "cCWHeavyWeapon", cCWHeavyWeapon::MakeNew, 0xA20, false);

    static GOM::cProtoRegistrar cCWHeavyWeaponSpawningRegistrar(
        cCWHeavyWeapon::StaticCreateClass(), cCWHeavyWeapon::SpawnFromPrototype);

    RWS::CAttributeHandler *cCWHeavyWeapon::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCWHeavyWeaponPrototype(packet);
    }

    const char *cCWHeavyWeapon::RetClassName() const
    {
        return "cCWHeavyWeapon";
    }

    RWS::CAttributeHandler *cCWHeavyWeapon::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cCWHeavyWeapon;
        return 0;
    }

    // CD2 script-type registration names this child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cCWHeavyWeapon> cCWHeavyWeaponScriptRegistrar(
        "cCWHeavyWeapon", "cCWWeapon");

    Fun_Runtime::cClass &cCWHeavyWeapon::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x4269, "cCWHeavyWeapon", 0xA20);
        return *descriptor;
    }

    const Fun_Runtime::cClass *cCWHeavyWeapon::ms_pcCWHeavyWeaponClass = &cCWHeavyWeapon::StaticCreateClass();

    const Fun_Runtime::cClass &cCWHeavyWeapon::RetClass() const
    {
        return *ms_pcCWHeavyWeaponClass;
    }

    bool cCWHeavyWeapon::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcCWHeavyWeaponClass->IsA(c);
    }

    // CD2 0x8262FCB0 has no derived cleanup beyond vtable restoration.
    cCWHeavyWeapon::~cCWHeavyWeapon()
    {
    }

    const Fun_Runtime::cScriptTypeRegistration *cCWHeavyWeapon::RetScriptTypeRegistration() const
    {
        return &cCWHeavyWeaponScriptRegistrar;
    }
}
