// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cLedgeAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cLedgeAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cLedgeProfileData::HandleAttributeData(*this, packet);
    }

    const char *cLedgeAnimationProfile::RetClassName() const
    {
        return "cLedgeAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cLedgeAnimationProfileRegistrar(
        "cLedgeAnimationProfile", cLedgeAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x825019E8: the class factory.
    RWS::CAttributeHandler *cLedgeAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cLedgeAnimationProfile;
    }
}
