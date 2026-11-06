// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cBeaconPulseHoverAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cBeaconPulseHoverAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataBeaconPulseHover::HandleAttributeData(*this, packet);
    }

    const char *cBeaconPulseHoverAnimationProfile::RetClassName() const
    {
        return "cBeaconPulseHoverAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cBeaconPulseHoverAnimationProfileRegistrar(
        "cBeaconPulseHoverAnimationProfile", cBeaconPulseHoverAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x824EC1A0: the class factory.
    RWS::CAttributeHandler *cBeaconPulseHoverAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cBeaconPulseHoverAnimationProfile;
    }
}
