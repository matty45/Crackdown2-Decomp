// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cTurretsAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cTurretsAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataTurrets::HandleAttributeData(*this, packet);
    }

    const char *cTurretsAnimationProfile::RetClassName() const
    {
        return "cTurretsAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cTurretsAnimationProfileRegistrar(
        "cTurretsAnimationProfile", cTurretsAnimationProfile::MakeNew, 0x48, false);

    // CD2 0x8250EEA8: the class factory.
    RWS::CAttributeHandler *cTurretsAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cTurretsAnimationProfile;
    }
}
