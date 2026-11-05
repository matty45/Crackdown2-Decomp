#include "Anim/cJumpLandFastAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cJumpLandFastAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataJumpLandFast::HandleAttributeData(*this, packet);
    }

    const char *cJumpLandFastAnimationProfile::RetClassName() const
    {
        return "cJumpLandFastAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cJumpLandFastAnimationProfileRegistrar(
        "cJumpLandFastAnimationProfile", cJumpLandFastAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x824F32E0: the class factory.
    RWS::CAttributeHandler *cJumpLandFastAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cJumpLandFastAnimationProfile;
    }
}
