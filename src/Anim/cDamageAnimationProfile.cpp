#include "Anim/cDamageAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cDamageAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cDamageProfileData::HandleAttributeData(*this, packet);
    }

    const char *cDamageAnimationProfile::RetClassName() const
    {
        return "cDamageAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cDamageAnimationProfileRegistrar(
        "cDamageAnimationProfile", cDamageAnimationProfile::MakeNew, 0x8C, false);

    // CD2 0x824F7B78: the class factory.
    RWS::CAttributeHandler *cDamageAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cDamageAnimationProfile;
    }
}
