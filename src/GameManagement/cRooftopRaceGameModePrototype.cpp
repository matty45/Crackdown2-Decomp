// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "GameManagement/cRooftopRaceGameModePrototype.h"

namespace GameManagement
{
    RWS::CAttributeHandler *cRooftopRaceGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cRooftopRaceGameModePrototype;
    }

    const char *cRooftopRaceGameModePrototype::RetClassName() const
    {
        return "cRooftopRaceGameModePrototype";
    }

    int cRooftopRaceGameModePrototype::RetStringID() const
    {
        return 0x1A2CF73E;
    }

    static RWS::CClassFactory::CRegistrar cRooftopRaceGameModePrototypeRegistrar(
        "cRooftopRaceGameModePrototype", cRooftopRaceGameModePrototype::MakeNew, 0x148, false);
}
