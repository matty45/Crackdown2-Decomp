#include "Anim/cHand2HandUpperAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cHand2HandUpperAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataHand2HandUpper::HandleAttributeData(*this, packet);
    }

    const char *cHand2HandUpperAnimationProfile::RetClassName() const
    {
        return "cHand2HandUpperAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cHand2HandUpperAnimationProfileRegistrar(
        "cHand2HandUpperAnimationProfile", cHand2HandUpperAnimationProfile::MakeNew, 0x70, false);
}

#include "cd2/memory.h"

// CD2 0x8251FE18: the class factory.
namespace Anim
{
    RWS::CAttributeHandler *cHand2HandUpperAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cHand2HandUpperAnimationProfile;
    }
}
