#include "Anim/cJumpAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cJumpAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataJump::HandleAttributeData(*this, packet);
    }

    const char *cJumpAnimationProfile::RetClassName() const
    {
        return "cJumpAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cJumpAnimationProfileRegistrar(
        "cJumpAnimationProfile", cJumpAnimationProfile::MakeNew, 0x40, false);
}

#include "cd2/memory.h"

// CD2 0x824EF728: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cJumpAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cJumpAnimationProfile;
    }
}
