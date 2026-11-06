// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cStandAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cStandAnimationProfile::RetClassName() const
    {
        return "cStandAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cStandAnimationProfileRegistrar(
        "cStandAnimationProfile", cStandAnimationProfile::MakeNew, 0x60, false);
}
