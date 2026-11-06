// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "unknown/cVehicleTagGameModePrototype.h"

namespace unknown
{
    const char *cVehicleTagGameModePrototype::RetClassName() const
    {
        return "cVehicleTagGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cVehicleTagGameModePrototypeRegistrar(
        "cVehicleTagGameModePrototype", cVehicleTagGameModePrototype::MakeNew, 0x238, false);
}
