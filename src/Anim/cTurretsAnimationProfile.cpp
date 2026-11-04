#include "Anim/cTurretsAnimationProfile.h"
#include "rws/classfactory.h"

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
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cTurretsAnimationProfileRegistrar(
        "cTurretsAnimationProfile", cTurretsAnimationProfile::MakeNew, 0x48, false);
}

#include "cd2/memory.h"

// CD2 0x8250EEA8: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cTurretsAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cTurretsAnimationProfile;
    }
}
