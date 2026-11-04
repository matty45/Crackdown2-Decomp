#include "Anim/cDamageAnimationProfile.h"
#include "rws/classfactory.h"

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
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cDamageAnimationProfileRegistrar(
        "cDamageAnimationProfile", cDamageAnimationProfile::MakeNew, 0x8C, false);
}

#include "cd2/memory.h"

// CD2 0x824F7B78: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cDamageAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cDamageAnimationProfile;
    }
}
