// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
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
