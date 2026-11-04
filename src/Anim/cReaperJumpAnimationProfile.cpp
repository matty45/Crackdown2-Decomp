#include "Anim/cReaperJumpAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cReaperJumpAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataReaperJump::HandleAttributeData(*this, packet);
    }

    const char *cReaperJumpAnimationProfile::RetClassName() const
    {
        return "cReaperJumpAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cReaperJumpAnimationProfileRegistrar(
        "cReaperJumpAnimationProfile", cReaperJumpAnimationProfile::MakeNew, 0x40, false);
}

#include "cd2/memory.h"

// CD2 0x824F66A0: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cReaperJumpAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cReaperJumpAnimationProfile;
    }
}
