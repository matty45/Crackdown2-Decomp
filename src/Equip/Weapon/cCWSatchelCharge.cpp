// src/Equip/Weapon/cCWSatchelCharge.cpp
//
// Class: cCWSatchelCharge (namespace: Equip). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cCWSatchelCharge.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cCWSatchelCharge.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cCWSatchelCharge.cpp

#include "rws/classfactory.h"
#include "Equip/cCWSatchelCharge.h"

// CD2 0x8261A210.
namespace Equip
{
    const char *cCWSatchelCharge::RetClassName() const
    {
        return "cCWSatchelCharge";
    }
}

// CD2 0x82FCF618 (initializer) and 0x8303F670 (at-exit destructor).
namespace Equip
{
    static RWS::CClassFactory::CRegistrar cCWSatchelChargeRegistrar(
        "cCWSatchelCharge", cCWSatchelCharge::MakeNew, 0xAE0, false);
}
