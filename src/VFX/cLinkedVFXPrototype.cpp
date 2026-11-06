#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "VFX/cLinkedVFXPrototype.h"

namespace VFX
{
    const char *cLinkedVFXPrototype::RetClassName() const
    {
        return "cLinkedVFXPrototype";
    }

    static RWS::CClassFactory::CRegistrar cLinkedVFXPrototypeRegistrar(
        "cLinkedVFXPrototype", cLinkedVFXPrototype::MakeNew, 0x44, false);
}
