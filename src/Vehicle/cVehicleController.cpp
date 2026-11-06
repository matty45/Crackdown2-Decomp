// src/Vehicle/cVehicleController.cpp
//
// Class: cVehicleController (namespace: Vehicle). Set up automatically: no function is matched yet. The address range
// and the evidence for it are in config/splits.txt; RuffKing's object for it is cVehicleController.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/burn_peb_ref/Burn/Main/Source/Code/Libraries/Shared/Vehicle/Controller/cVehicleController.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Vehicle/cVehicleController.cpp

// CD2 0x83005288: runtime class inheritance registration.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "VEHICLE_CONTROL/cHelicopterController.h"
#include "gom/non_game_base.h"
#include "cd2/memory.h"
#include "rws/classfactory.h"

namespace VEHICLE_CONTROL
{
    const Fun_Runtime::cClass *cVehicleController::ms_pcVehicleControllerClass = &cVehicleController::StaticCreateClass();

    Fun_Runtime::cClass &cVehicleController::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cVehicleControllerClass =
            new Fun_Runtime::cClass(14, "cVehicleController", 0x840);
        return *cVehicleControllerClass;
    }

    static Fun_Runtime::cInheritanceRegistrar cVehicleControllercNonGameBaseInheritRegistrar(
        VEHICLE_CONTROL::cVehicleController::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    // CD2 0x830052F0: register the class factory.
    static RWS::CClassFactory::CRegistrar cVehicleControllerRegistrar(
        "cVehicleController", cVehicleController::MakeNew, 0x840, false);

    // CD2 0x83005340: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cVehicleControllerSpawningRegistrar(
        cVehicleController::StaticCreateClass(), cVehicleController::SpawnFromPrototype);

    RWS::CAttributeHandler *cVehicleController::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cVehicleControllerPrototype(packet);
    }

    const char *cVehicleController::RetClassName() const
    {
        return "cVehicleController";
    }

    void cVehicleController::AssignVehicle(Vehicle::cVehicle *vehicle)
    {
        m_pVehicle = vehicle;
    }

    RWS::CAttributeHandler *cVehicleController::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cVehicleController;
        return 0;
    }
}
