#include "rws/classfactory.h"
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

#include "Equip/cHWGrenadeProjectile.h"

namespace Equip
{
    const char *cHWGrenadeProjectile::RetClassName() const
    {
        return "cHWGrenadeProjectile";
    }
}

#include "cd2/memory.h"

namespace Equip
{
    Fun_Runtime::cClass &cHWGrenadeProjectile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cHWGrenadeProjectileClass = new Fun_Runtime::cClass(0x4275, "cHWGrenadeProjectile", 0xA40);
        return *cHWGrenadeProjectileClass;
    }
}

namespace Equip
{
    const Fun_Runtime::cClass *cHWGrenadeProjectile::ms_pcHWGrenadeProjectileClass = &cHWGrenadeProjectile::StaticCreateClass();
}

namespace Equip
{
    static RWS::CClassFactory::CRegistrar cHWGrenadeProjectileRegistrar(
        "cHWGrenadeProjectile", cHWGrenadeProjectile::MakeNew, 0xA40, false);
}
