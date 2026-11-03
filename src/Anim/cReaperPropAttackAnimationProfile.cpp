#include "Anim/cReaperPropAttackAnimationProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    void cReaperPropAttackAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataReaperPropAttack::HandleAttributeData(*this, packet);
    }

    const char *cReaperPropAttackAnimationProfile::RetClassName() const
    {
        return "cReaperPropAttackAnimationProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cReaperPropAttackAnimationProfileRegistrar(
        "cReaperPropAttackAnimationProfile", cReaperPropAttackAnimationProfile::MakeNew, 0x44, false);
}
