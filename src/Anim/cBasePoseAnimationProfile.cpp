// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cBasePoseAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cBasePoseAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataBasePose::HandleAttributeData(*this, packet);
    }

    const char *cBasePoseAnimationProfile::RetClassName() const
    {
        return "cBasePoseAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cBasePoseAnimationProfileRegistrar(
        "cBasePoseAnimationProfile", cBasePoseAnimationProfile::MakeNew, 0x40, false);
}
