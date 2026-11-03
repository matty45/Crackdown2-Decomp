#include "fun_runtime/inheritance_registrar.h"
#include "Equip/cCWWeapon.h"
#include "rws/classfactory.h"
// src/Equip/Gadget/cPulseRifle.cpp
//
// Class: cPulseRifle (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cPulseRifle.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Gadget/cPulseRifle.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Gadget/cPulseRifle.cpp

#include "Equip/cPulseRifle.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cPulseRifle::ms_pcPulseRifleClass = &cPulseRifle::StaticCreateClass();

    Fun_Runtime::cClass &cPulseRifle::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPulseRifleClass = new Fun_Runtime::cClass(0x27413, "cPulseRifle", 0xA80);
        return *cPulseRifleClass;
    }
}

namespace Equip
{
    static RWS::CClassFactory::CRegistrar cPulseRifleRegistrar(
        "cPulseRifle", cPulseRifle::MakeNew, 0xA80, false);
}

// CD2 0x82FCD220: runtime class inheritance registration.
namespace Equip
{
    static Fun_Runtime::cInheritanceRegistrar cPulseRiflecCWWeaponInheritRegistrar(
        Equip::cPulseRifle::StaticCreateClass(), Equip::cCWWeapon::StaticCreateClass());
}
