// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cWingSuitAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cWingSuitAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataWingSuit::HandleAttributeData(*this, packet);
    }

    const char *cWingSuitAnimationProfile::RetClassName() const
    {
        return "cWingSuitAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cWingSuitAnimationProfileRegistrar(
        "cWingSuitAnimationProfile", cWingSuitAnimationProfile::MakeNew, 0xDC, false);

    // CD2 0x824F3DB0: the class factory.
    RWS::CAttributeHandler *cWingSuitAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cWingSuitAnimationProfile;
    }
}
