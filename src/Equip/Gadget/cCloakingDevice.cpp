// src/Equip/Gadget/cCloakingDevice.cpp
//
// Class: cCloakingDevice (namespace: Equip). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cCloakingDevice.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Gadget/cCloakingDevice.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Gadget/cCloakingDevice.cpp

#include "rws/classfactory.h"
#include "Equip/cCloakingDevice.h"

// CD2 0x8260B278.
namespace Equip
{
    const char *cCloakingDevice::RetClassName() const
    {
        return "cCloakingDevice";
    }
}

// CD2 0x82FCC720 (initializer) and 0x8303F418 (at-exit destructor).
namespace Equip
{
    static RWS::CClassFactory::CRegistrar cCloakingDeviceRegistrar(
        "cCloakingDevice", cCloakingDevice::MakeNew, 0x9C0, false);
}
