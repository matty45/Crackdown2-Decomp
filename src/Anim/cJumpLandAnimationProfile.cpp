#include "Anim/cJumpLandAnimationProfile.h"
#include "rws/classfactory.h"

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
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cJumpLandAnimationProfileRegistrar(
        "cJumpLandAnimationProfile", cJumpLandAnimationProfile::MakeNew, 0x4C, false);
}

#include "cd2/memory.h"

// CD2 0x824F1688: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cJumpLandAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cJumpLandAnimationProfile;
    }
}
