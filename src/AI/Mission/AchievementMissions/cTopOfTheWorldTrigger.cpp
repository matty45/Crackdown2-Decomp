// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cTopOfTheWorldTrigger.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cTopOfTheWorldTrigger::RetClassName() const
    {
        return "cTopOfTheWorldTrigger";
    }

    static RWS::CClassFactory::CRegistrar cTopOfTheWorldTriggerRegistrar(
        "cTopOfTheWorldTrigger", cTopOfTheWorldTrigger::MakeNew, 0xE0, false);
}
