#include "Anim/cHand2HandFullAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cHand2HandFullAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataHand2HandFull::HandleAttributeData(*this, packet);
    }

    const char *cHand2HandFullAnimationProfile::RetClassName() const
    {
        return "cHand2HandFullAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cHand2HandFullAnimationProfileRegistrar(
        "cHand2HandFullAnimationProfile", cHand2HandFullAnimationProfile::MakeNew, 0x3EE0, false);
}

#include "cd2/memory.h"

namespace Anim
{
    RWS::CAttributeHandler *cHand2HandFullAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cHand2HandFullAnimationProfile;
    }
}
