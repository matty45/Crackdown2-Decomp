#include "Anim/cGoliathAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cGoliathAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataGoliath::HandleAttributeData(*this, packet);
    }

    const char *cGoliathAnimationProfile::RetClassName() const
    {
        return "cGoliathAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cGoliathAnimationProfileRegistrar(
        "cGoliathAnimationProfile", cGoliathAnimationProfile::MakeNew, 0x4C, false);
}

#include "cd2/memory.h"

// CD2 0x824ECF80: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cGoliathAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGoliathAnimationProfile;
    }
}
