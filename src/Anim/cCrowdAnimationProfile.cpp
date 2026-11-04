#include "Anim/cCrowdAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cCrowdAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataCrowd::HandleAttributeData(*this, packet);
    }

    const char *cCrowdAnimationProfile::RetClassName() const
    {
        return "cCrowdAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cCrowdAnimationProfileRegistrar(
        "cCrowdAnimationProfile", cCrowdAnimationProfile::MakeNew, 0x40, false);
}

#include "cd2/memory.h"

// CD2 0x82524D88: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cCrowdAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCrowdAnimationProfile;
    }
}
