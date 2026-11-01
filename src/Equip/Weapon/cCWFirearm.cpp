#include "rws/classfactory.h"
// src/Equip/Weapon/cCWFirearm.cpp
//
// Class: cCWFirearm (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cCWFirearm.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cCWFirearm.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cCWFirearm.cpp

#include "Equip/cCWFirearm.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cCWFirearm::ms_pcCWFirearmClass = &cCWFirearm::StaticCreateClass();

    Fun_Runtime::cClass &cCWFirearm::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCWFirearmClass = new Fun_Runtime::cClass(0x3E81, "cCWFirearm", 0xAB0);
        return *cCWFirearmClass;
    }
}

namespace Equip
{
    static RWS::CClassFactory::CRegistrar cCWFirearmRegistrar(
        "cCWFirearm", cCWFirearm::MakeNew, 0xAB0, false);
}
