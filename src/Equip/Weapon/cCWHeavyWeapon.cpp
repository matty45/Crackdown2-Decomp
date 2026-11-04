#include "cd2/memory.h"
#include "Equip/cCWHeavyWeapon.h"
#include "gom/proto_registrar.h"
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
namespace Equip
{
    static GOM::cProtoRegistrar cCWHeavyWeaponSpawningRegistrar(
        cCWHeavyWeapon::StaticCreateClass(), cCWHeavyWeapon::SpawnFromPrototype);
}

namespace Equip
{
    const char *cCWHeavyWeapon::RetClassName() const
    {
        return "cCWHeavyWeapon";
    }
}

namespace Equip
{
    RWS::CAttributeHandler *cCWHeavyWeapon::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cCWHeavyWeapon;
        return 0;
    }
}

#include "Equip/cCWHeavyWeapon.h"
#include "fun_runtime/script_type_registrar.h"

namespace Equip
{
    // CD2 script-type registration names this child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cCWHeavyWeapon> cCWHeavyWeaponScriptRegistrar(
        "cCWHeavyWeapon", "cCWWeapon");
}

#include "cd2/memory.h"

namespace Equip
{
    Fun_Runtime::cClass &cCWHeavyWeapon::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x4269, "cCWHeavyWeapon", 0xA20);
        return *descriptor;
    }
}

namespace Equip
{
    const Fun_Runtime::cClass *cCWHeavyWeapon::ms_pcCWHeavyWeaponClass = &cCWHeavyWeapon::StaticCreateClass();

    const Fun_Runtime::cClass &cCWHeavyWeapon::RetClass() const
    {
        return *ms_pcCWHeavyWeaponClass;
    }
}
