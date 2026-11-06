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
