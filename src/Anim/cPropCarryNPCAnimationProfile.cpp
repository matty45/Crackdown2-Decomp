#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cPropCarryNPCAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cPropCarryNPCAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataPropCarryNPC::HandleAttributeData(*this, packet);
    }

    const char *cPropCarryNPCAnimationProfile::RetClassName() const
    {
        return "cPropCarryNPCAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cPropCarryNPCAnimationProfileRegistrar(
        "cPropCarryNPCAnimationProfile", cPropCarryNPCAnimationProfile::MakeNew, 0x4C, false);
}
