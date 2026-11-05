#include "Anim/cPropPickUpFullAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

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

    static RWS::CClassFactory::CRegistrar cPropPickUpFullAnimationProfileRegistrar(
        "cPropPickUpFullAnimationProfile", cPropPickUpFullAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x8250CF18: the class factory.
    RWS::CAttributeHandler *cPropPickUpFullAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cPropPickUpFullAnimationProfile;
    }
}
