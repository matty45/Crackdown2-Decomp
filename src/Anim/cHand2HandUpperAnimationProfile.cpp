#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cHand2HandUpperAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cHand2HandUpperAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataHand2HandUpper::HandleAttributeData(*this, packet);
    }

    const char *cHand2HandUpperAnimationProfile::RetClassName() const
    {
        return "cHand2HandUpperAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cHand2HandUpperAnimationProfileRegistrar(
        "cHand2HandUpperAnimationProfile", cHand2HandUpperAnimationProfile::MakeNew, 0x70, false);

    // CD2 0x8251FE18: the class factory.
    RWS::CAttributeHandler *cHand2HandUpperAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cHand2HandUpperAnimationProfile;
    }
}
