#include "Anim/cCoverAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cCoverAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataCover::HandleAttributeData(*this, packet);
    }

    const char *cCoverAnimationProfile::RetClassName() const
    {
        return "cCoverAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cCoverAnimationProfileRegistrar(
        "cCoverAnimationProfile", cCoverAnimationProfile::MakeNew, 0x40, false);
}
