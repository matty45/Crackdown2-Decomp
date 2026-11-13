// Audio/cWorldGameObject.cpp: RuffKing's Libraries/Shared/Audio/cWorldGameObject.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/class.h"
#include "rws/classfactory.h"
#include "Audio/cWorldGameObject.h"
#include "cd2/memory.h"

namespace Audio
{
    const char *cWorldGameObject::RetClassName() const
    {
        return "cWorldGameObject";
    }

    static RWS::CClassFactory::CRegistrar cWorldGameObjectRegistrar(
        "cWorldGameObject", cWorldGameObject::MakeNew, 0x1040, false);
}
