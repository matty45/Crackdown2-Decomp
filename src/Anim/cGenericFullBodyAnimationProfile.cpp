#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cGenericFullBodyAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cGenericFullBodyAnimationProfile::RetClassName() const
    {
        return "cGenericFullBodyAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cGenericFullBodyAnimationProfileRegistrar(
        "cGenericFullBodyAnimationProfile", cGenericFullBodyAnimationProfile::MakeNew, 0x40, false);
}
