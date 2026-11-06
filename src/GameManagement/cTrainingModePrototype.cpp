#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "GameManagement/cTrainingModePrototype.h"

namespace GameManagement
{
    const char *cTrainingModePrototype::RetClassName() const
    {
        return "cTrainingModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cTrainingModePrototypeRegistrar(
        "cTrainingModePrototype", cTrainingModePrototype::MakeNew, 0x110, false);
}
