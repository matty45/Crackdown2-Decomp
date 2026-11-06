// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cHand2HandFullAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cHand2HandFullAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataHand2HandFull::HandleAttributeData(*this, packet);
    }

    const char *cHand2HandFullAnimationProfile::RetClassName() const
    {
        return "cHand2HandFullAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cHand2HandFullAnimationProfileRegistrar(
        "cHand2HandFullAnimationProfile", cHand2HandFullAnimationProfile::MakeNew, 0x3EE0, false);

    RWS::CAttributeHandler *cHand2HandFullAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cHand2HandFullAnimationProfile;
    }
}
