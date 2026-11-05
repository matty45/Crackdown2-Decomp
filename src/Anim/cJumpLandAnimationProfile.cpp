#include "Anim/cJumpLandAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cJumpLandAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataJumpLand::HandleAttributeData(*this, packet);
    }

    const char *cJumpLandAnimationProfile::RetClassName() const
    {
        return "cJumpLandAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cJumpLandAnimationProfileRegistrar(
        "cJumpLandAnimationProfile", cJumpLandAnimationProfile::MakeNew, 0x4C, false);

    // CD2 0x824F1688: the class factory.
    RWS::CAttributeHandler *cJumpLandAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cJumpLandAnimationProfile;
    }
}
