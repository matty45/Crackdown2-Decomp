#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cLedgeAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cLedgeAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cLedgeProfileData::HandleAttributeData(*this, packet);
    }

    const char *cLedgeAnimationProfile::RetClassName() const
    {
        return "cLedgeAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cLedgeAnimationProfileRegistrar(
        "cLedgeAnimationProfile", cLedgeAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x825019E8: the class factory.
    RWS::CAttributeHandler *cLedgeAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cLedgeAnimationProfile;
    }
}
