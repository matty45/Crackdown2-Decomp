#include "Anim/cSprintAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    float cProfileDataSprint::RetSprintBargeHitTime() const
    {
        return m_fSprintBargeHitTime;
    }

    void cSprintAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataSprint::HandleAttributeData(*this, packet);
    }

    const char *cSprintAnimationProfile::RetClassName() const
    {
        return "cSprintAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cSprintAnimationProfileRegistrar(
        "cSprintAnimationProfile", cSprintAnimationProfile::MakeNew, 0x6C, false);

    // CD2 0x825218B8: the class factory.
    RWS::CAttributeHandler *cSprintAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cSprintAnimationProfile;
    }
}
