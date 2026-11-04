#include "rws/classfactory.h"
// src/Equip/Weapon/cMag.cpp
//
// Class: cMag (namespace: Equip). Set up automatically: no function is matched yet. The address range and the evidence
// for it are in config/splits.txt; RuffKing's object for it is cMag.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cMag.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cMag.cpp

#include "Equip/cMag.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cMag::ms_pcMagClass = &cMag::StaticCreateClass();

    Fun_Runtime::cClass &cMag::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cMagClass = new Fun_Runtime::cClass(0x27411, "cMag", 0xB20);
        return *cMagClass;
    }
}

namespace Equip
{
    static RWS::CClassFactory::CRegistrar cMagRegistrar(
        "cMag", cMag::MakeNew, 0xB20, false);
}

// CD2 0x8260BC50.
namespace Equip
{
    const char *cMag::RetClassName() const
    {
        return "cMag";
    }
}
