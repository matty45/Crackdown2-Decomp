// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cGenericUpperBodyAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cGenericUpperBodyAnimationProfile::RetClassName() const
    {
        return "cGenericUpperBodyAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cGenericUpperBodyAnimationProfileRegistrar(
        "cGenericUpperBodyAnimationProfile", cGenericUpperBodyAnimationProfile::MakeNew, 0x40, false);
}
