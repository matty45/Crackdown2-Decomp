// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cRappelAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cRappelAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataRappel::HandleAttributeData(*this, packet);
    }

    const char *cRappelAnimationProfile::RetClassName() const
    {
        return "cRappelAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cRappelAnimationProfileRegistrar(
        "cRappelAnimationProfile", cRappelAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x824EF200: the class factory.
    RWS::CAttributeHandler *cRappelAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cRappelAnimationProfile;
    }
}
