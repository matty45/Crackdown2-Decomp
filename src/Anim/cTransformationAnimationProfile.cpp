#include "Anim/cTransformationAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cTransformationAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataTransformation::HandleAttributeData(*this, packet);
    }

    const char *cTransformationAnimationProfile::RetClassName() const
    {
        return "cTransformationAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cTransformationAnimationProfileRegistrar(
        "cTransformationAnimationProfile", cTransformationAnimationProfile::MakeNew, 0x40, false);
}

#include "cd2/memory.h"

// CD2 0x825247E8: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cTransformationAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cTransformationAnimationProfile;
    }
}
