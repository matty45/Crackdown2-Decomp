// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "GameManagement/cTagGameModePrototype.h"

namespace GameManagement
{
    const char *cTagGameModePrototype::RetClassName() const
    {
        return "cTagGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cTagGameModePrototypeRegistrar(
        "cTagGameModePrototype", cTagGameModePrototype::MakeNew, 0x1d8, false);
}
