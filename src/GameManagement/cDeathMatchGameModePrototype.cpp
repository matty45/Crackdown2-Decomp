#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "GameManagement/cDeathMatchGameModePrototype.h"

namespace GameManagement
{
    const char *cDeathMatchGameModePrototype::RetClassName() const
    {
        return "cDeathMatchGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cDeathMatchGameModePrototypeRegistrar(
        "cDeathMatchGameModePrototype", cDeathMatchGameModePrototype::MakeNew, 0x190, false);
}
