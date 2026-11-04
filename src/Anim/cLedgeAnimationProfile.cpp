#include "Anim/cLedgeAnimationProfile.h"
#include "rws/classfactory.h"

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
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cLedgeAnimationProfileRegistrar(
        "cLedgeAnimationProfile", cLedgeAnimationProfile::MakeNew, 0x40, false);
}

#include "cd2/memory.h"

// CD2 0x825019E8: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cLedgeAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cLedgeAnimationProfile;
    }
}
