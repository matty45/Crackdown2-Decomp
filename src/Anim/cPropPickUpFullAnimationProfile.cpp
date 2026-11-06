// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cPropPickUpFullAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cPropPickUpFullAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataPropPickUpFull::HandleAttributeData(*this, packet);
    }

    const char *cPropPickUpFullAnimationProfile::RetClassName() const
    {
        return "cPropPickUpFullAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cPropPickUpFullAnimationProfileRegistrar(
        "cPropPickUpFullAnimationProfile", cPropPickUpFullAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x8250CF18: the class factory.
    RWS::CAttributeHandler *cPropPickUpFullAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cPropPickUpFullAnimationProfile;
    }
}
