#include "rws/classfactory.h"
// src/Equip/Weapon/cSmokeGrenade.cpp
//
// Class: cSmokeGrenade (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cSmokeGrenade.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cSmokeGrenade.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cSmokeGrenade.cpp

#include "Equip/cSmokeGrenade.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cSmokeGrenade::ms_pcSmokeGrenadeClass = &cSmokeGrenade::StaticCreateClass();

    Fun_Runtime::cClass &cSmokeGrenade::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSmokeGrenadeClass = new Fun_Runtime::cClass(0x3E8D, "cSmokeGrenade", 0x9D0);
        return *cSmokeGrenadeClass;
    }
}

namespace Equip
{
    static RWS::CClassFactory::CRegistrar cSmokeGrenadeRegistrar(
        "cSmokeGrenade", cSmokeGrenade::MakeNew, 0x9D0, false);
}

// CD2 0x826225D0.
namespace Equip
{
    const Fun_Runtime::cClass &cSmokeGrenade::RetClass() const
    {
        return *ms_pcSmokeGrenadeClass;
    }
}

// CD2 0x826226C0.
namespace Equip
{
    const char *cSmokeGrenade::RetClassName() const
    {
        return "cSmokeGrenade";
    }
}
