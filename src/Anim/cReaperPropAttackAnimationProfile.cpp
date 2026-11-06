#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cReaperPropAttackAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

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

    static RWS::CClassFactory::CRegistrar cReaperPropAttackAnimationProfileRegistrar(
        "cReaperPropAttackAnimationProfile", cReaperPropAttackAnimationProfile::MakeNew, 0x44, false);

    // CD2 0x824EC6E0: the class factory.
    RWS::CAttributeHandler *cReaperPropAttackAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cReaperPropAttackAnimationProfile;
    }
}
