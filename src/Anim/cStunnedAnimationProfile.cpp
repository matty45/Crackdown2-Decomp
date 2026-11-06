// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cStunnedAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cStunnedAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cStunnedProfileData::HandleAttributeData(*this, packet);
    }

    const char *cStunnedAnimationProfile::RetClassName() const
    {
        return "cStunnedAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cStunnedAnimationProfileRegistrar(
        "cStunnedAnimationProfile", cStunnedAnimationProfile::MakeNew, 0x44, false);

    // CD2 0x82500428: the class factory.
    RWS::CAttributeHandler *cStunnedAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cStunnedAnimationProfile;
    }
}
