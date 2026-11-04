#include "Anim/cReactionAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cReactionAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataReaction::HandleAttributeData(*this, packet);
    }

    const char *cReactionAnimationProfile::RetClassName() const
    {
        return "cReactionAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cReactionAnimationProfileRegistrar(
        "cReactionAnimationProfile", cReactionAnimationProfile::MakeNew, 0x40, false);
}

#include "cd2/memory.h"

// CD2 0x824ED960: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cReactionAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cReactionAnimationProfile;
    }
}
