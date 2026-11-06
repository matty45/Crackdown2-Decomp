// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cDamageAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cDamageAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cDamageProfileData::HandleAttributeData(*this, packet);
    }

    const char *cDamageAnimationProfile::RetClassName() const
    {
        return "cDamageAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cDamageAnimationProfileRegistrar(
        "cDamageAnimationProfile", cDamageAnimationProfile::MakeNew, 0x8C, false);

    // CD2 0x824F7B78: the class factory.
    RWS::CAttributeHandler *cDamageAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cDamageAnimationProfile;
    }
}
