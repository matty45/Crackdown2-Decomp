#include "rws/classfactory.h"
// src/Equip/DLCWeapons/cProxMine.cpp
//
// Class: cProxMine (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cProxMine.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/DLCWeapons/cProxMine.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/DLCWeapons/cProxMine.cpp

#include "Equip/cProxMine.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cProxMine::ms_pcProxMineClass = &cProxMine::StaticCreateClass();

    Fun_Runtime::cClass &cProxMine::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cProxMineClass = new Fun_Runtime::cClass(0x13265, "cProxMine", 0xB10);
        return *cProxMineClass;
    }
}

namespace Equip
{
    static RWS::CClassFactory::CRegistrar cProxMineRegistrar(
        "cProxMine", cProxMine::MakeNew, 0xB10, false);
}

// CD2 0x8261F870.
namespace Equip
{
    const Fun_Runtime::cClass &cProxMine::RetClass() const
    {
        return *ms_pcProxMineClass;
    }
}

// CD2 0x8261F938.
namespace Equip
{
    const char *cProxMine::RetClassName() const
    {
        return "cProxMine";
    }
}

#include "fun_runtime/inheritance_registrar.h"
#include "Equip/cCWSatchelCharge.h"

// CD2 0x82FD03B8: runtime class inheritance registration.
namespace Equip
{
    static Fun_Runtime::cInheritanceRegistrar cProxMinecCWSatchelChargeInheritRegistrar(
        Equip::cProxMine::StaticCreateClass(), Equip::cCWSatchelCharge::StaticCreateClass());
}
