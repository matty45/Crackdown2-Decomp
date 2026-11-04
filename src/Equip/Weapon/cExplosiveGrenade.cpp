// src/Equip/Weapon/cExplosiveGrenade.cpp
//
// Class: cExplosiveGrenade (namespace: Equip). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cExplosiveGrenade.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cExplosiveGrenade.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cExplosiveGrenade.cpp

#include "rws/classfactory.h"
#include "Equip/cExplosiveGrenade.h"

// CD2 0x8261D210.
namespace Equip
{
    const char *cExplosiveGrenade::RetClassName() const
    {
        return "cExplosiveGrenade";
    }
}

// CD2 0x82FCFAA8 (initializer) and 0x8303F6B0 (at-exit destructor).
namespace Equip
{
    static RWS::CClassFactory::CRegistrar cExplosiveGrenadeRegistrar(
        "cExplosiveGrenade", cExplosiveGrenade::MakeNew, 0x9D0, false);
}
