#include "rws/classfactory.h"
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
}

namespace Equip
{
    static RWS::CClassFactory::CRegistrar cClusterGrenadeRegistrar(
        "cClusterGrenade", cClusterGrenade::MakeNew, 0x9D0, false);
}

// CD2 0x826197B8.
namespace Equip
{
    const char *cClusterGrenade::RetClassName() const
    {
        return "cClusterGrenade";
    }
}
