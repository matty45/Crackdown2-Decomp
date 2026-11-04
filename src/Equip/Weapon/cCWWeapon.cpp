#include "rws/classfactory.h"
// src/Equip/Weapon/cCWWeapon.cpp
//
// Class: cCWWeapon (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cCWWeapon.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cCWWeapon.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cCWWeapon.cpp

#include "Equip/cCWWeapon.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cCWWeapon::ms_pcCWWeaponClass = &cCWWeapon::StaticCreateClass();

    Fun_Runtime::cClass &cCWWeapon::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCWWeaponClass = new Fun_Runtime::cClass(0x3E82, "cCWWeapon", 0xA10);
        return *cCWWeaponClass;
    }
}

namespace Equip
{
    static RWS::CClassFactory::CRegistrar cCWWeaponRegistrar(
        "cCWWeapon", cCWWeapon::MakeNew, 0xA10, false);
}

#include "fun_runtime/inheritance_registrar.h"
#include "Equip/cWeapon.h"

// CD2 0x82FCB7D8: runtime class inheritance registration.
namespace Equip
{
    static Fun_Runtime::cInheritanceRegistrar cCWWeaponcWeaponInheritRegistrar(
        Equip::cCWWeapon::StaticCreateClass(), Equip::cWeapon::StaticCreateClass());
}
