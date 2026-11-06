// src/GangManager/cAgressiveResponseTurretVehicleSetup.cpp
//
// Class: cAgressiveResponseTurretVehicleSetup (namespace: GangManager). Set up automatically: no function is matched
// yet. The address range and the evidence for it are in config/splits.txt; RuffKing's object for it is
// cAgressiveResponseTurretVehicleSetup.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/burn_peb_ref/Burn/Main/Source/Code/Libraries/Shared/GangManager/cAgressiveResponseTurretVehicleSetup.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/GangManager/cAgressiveResponseTurretVehicleSetup.cpp


// CD2 0x82FDBE70 (initializer) and 0x83040218 (at-exit destructor).

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "rws/classfactory.h"
#include "GangManager/cAgressiveResponseTurretVehicleSetup.h"

namespace GangManager
{
    static RWS::CClassFactory::CRegistrar cAgressiveResponseTurretVehicleSetupRegistrar(
        "cAgressiveResponseTurretVehicleSetup", cAgressiveResponseTurretVehicleSetup::MakeNew, 0x68, false);
}
