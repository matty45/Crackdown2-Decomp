#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "unknown/cKeysToTheCityGameModePrototype.h"

namespace unknown
{
    const char *cKeysToTheCityGameModePrototype::RetClassName() const
    {
        return "cKeysToTheCityGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cKeysToTheCityGameModePrototypeRegistrar(
        "cKeysToTheCityGameModePrototype", cKeysToTheCityGameModePrototype::MakeNew, 0x120, false);
}
