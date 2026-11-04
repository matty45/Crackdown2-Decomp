#include "Anim/cPropPickUpFullAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cPropPickUpFullAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataPropPickUpFull::HandleAttributeData(*this, packet);
    }

    const char *cPropPickUpFullAnimationProfile::RetClassName() const
    {
        return "cPropPickUpFullAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cPropPickUpFullAnimationProfileRegistrar(
        "cPropPickUpFullAnimationProfile", cPropPickUpFullAnimationProfile::MakeNew, 0x40, false);
}

#include "cd2/memory.h"

// CD2 0x8250CF18: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cPropPickUpFullAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cPropPickUpFullAnimationProfile;
    }
}
