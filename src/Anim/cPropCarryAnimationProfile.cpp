#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cPropCarryAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cPropCarryAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataPropCarry::HandleAttributeData(*this, packet);
    }

    const char *cPropCarryAnimationProfile::RetClassName() const
    {
        return "cPropCarryAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cPropCarryAnimationProfileRegistrar(
        "cPropCarryAnimationProfile", cPropCarryAnimationProfile::MakeNew, 0x44, false);
}
