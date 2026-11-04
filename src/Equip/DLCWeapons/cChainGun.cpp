#include "fun_runtime/inheritance_registrar.h"
#include "Equip/cCWFirearm.h"
#include "rws/classfactory.h"
// src/Equip/DLCWeapons/cChainGun.cpp
//
// Class: cChainGun (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cChainGun.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/DLCWeapons/cChainGun.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/DLCWeapons/cChainGun.cpp

#include "Equip/cChainGun.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cChainGun::ms_pcChainGunClass = &cChainGun::StaticCreateClass();

    Fun_Runtime::cClass &cChainGun::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cChainGunClass = new Fun_Runtime::cClass(0x13266, "cChainGun", 0xAC0);
        return *cChainGunClass;
    }
}

namespace Equip
{
    static RWS::CClassFactory::CRegistrar cChainGunRegistrar(
        "cChainGun", cChainGun::MakeNew, 0xAC0, false);
}

// CD2 0x82FCE550: runtime class inheritance registration.
namespace Equip
{
    static Fun_Runtime::cInheritanceRegistrar cChainGuncCWFirearmInheritRegistrar(
        Equip::cChainGun::StaticCreateClass(), Equip::cCWFirearm::StaticCreateClass());
}

// CD2 0x826165A8.
namespace Equip
{
    const char *cChainGun::RetClassName() const
    {
        return "cChainGun";
    }
}
