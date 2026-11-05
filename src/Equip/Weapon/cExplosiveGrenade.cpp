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

#include "Equip/cExplosiveGrenade.h"
#include "fun_runtime/script_type_registrar.h"
#include "cd2/memory.h"

namespace Equip
{
    const char *cExplosiveGrenade::RetClassName() const
    {
        return "cExplosiveGrenade";
    }

    // CD2 script-type registration names this child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cExplosiveGrenade> cExplosiveGrenadeScriptRegistrar(
        "cExplosiveGrenade", "cGrenade");

    Fun_Runtime::cClass &cExplosiveGrenade::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x3E8B, "cExplosiveGrenade", 0x9D0);
        return *descriptor;
    }

    const Fun_Runtime::cClass *cExplosiveGrenade::ms_pcExplosiveGrenadeClass = &cExplosiveGrenade::StaticCreateClass();

    const Fun_Runtime::cClass &cExplosiveGrenade::RetClass() const
    {
        return *ms_pcExplosiveGrenadeClass;
    }
}
