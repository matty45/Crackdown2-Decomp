#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "VEHICLE_CONTROL/cHelicopterController.h"
#include "PHYSICS/cNetDynamicBody.h"
// src/Vehicle/cVehicle.cpp
//
// Class: cVehicle (namespace: Vehicle). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cVehicle.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Vehicle/cVehicle.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Vehicle/cVehicle.cpp

// CD2 0x82FE9970: runtime class inheritance registration.
namespace Vehicle
{
    static Fun_Runtime::cInheritanceRegistrar cVehiclecNetDynamicBodyInheritRegistrar(
        Vehicle::cVehicle::StaticCreateClass(), PHYSICS::cNetDynamicBody::StaticCreateClass());
}

// CD2 0x82FE9A28: register the class descriptor and placement factory.
namespace Vehicle
{
    static GOM::cProtoRegistrar cVehicleSpawningRegistrar(
        cVehicle::StaticCreateClass(), cVehicle::SpawnFromPrototype);
}

namespace Vehicle
{
    const char *cVehicle::RetClassName() const
    {
        return "cVehicle";
    }
}

#include "VEHICLE_CONTROL/cHelicopterController.h"
#include "fun_runtime/script_type_registrar.h"

namespace Vehicle
{
    // CD2 script-type registration names this child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cVehicle> cVehicleScriptRegistrar(
        "cVehicle", "cDynamicBody");
}

#include "cd2/memory.h"

namespace Vehicle
{
    Fun_Runtime::cClass &cVehicle::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x1, "cVehicle", 0x1740);
        return *descriptor;
    }
}

namespace Vehicle
{
    const Fun_Runtime::cClass *cVehicle::ms_pcVehicleClass = &cVehicle::StaticCreateClass();
}
