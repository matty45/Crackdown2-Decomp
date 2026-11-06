// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cPropThrowAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cPropThrowAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataPropThrow::HandleAttributeData(*this, packet);
    }

    const char *cPropThrowAnimationProfile::RetClassName() const
    {
        return "cPropThrowAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cPropThrowAnimationProfileRegistrar(
        "cPropThrowAnimationProfile", cPropThrowAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x8250D9A0: the class factory.
    RWS::CAttributeHandler *cPropThrowAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cPropThrowAnimationProfile;
    }
}
