#include "Anim/cNPCBargeAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cNPCBargeAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataNPCBarge::HandleAttributeData(*this, packet);
    }

    const char *cNPCBargeAnimationProfile::RetClassName() const
    {
        return "cNPCBargeAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cNPCBargeAnimationProfileRegistrar(
        "cNPCBargeAnimationProfile", cNPCBargeAnimationProfile::MakeNew, 0x50, false);
}

#include "cd2/memory.h"

// CD2 0x824EAF90: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cNPCBargeAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cNPCBargeAnimationProfile;
    }
}
