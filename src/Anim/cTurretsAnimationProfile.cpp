#include "Anim/cTurretsAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cTurretsAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataTurrets::HandleAttributeData(*this, packet);
    }

    const char *cTurretsAnimationProfile::RetClassName() const
    {
        return "cTurretsAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cTurretsAnimationProfileRegistrar(
        "cTurretsAnimationProfile", cTurretsAnimationProfile::MakeNew, 0x48, false);

    // CD2 0x8250EEA8: the class factory.
    RWS::CAttributeHandler *cTurretsAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cTurretsAnimationProfile;
    }
}
