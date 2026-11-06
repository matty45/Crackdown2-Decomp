#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cPropPickUpAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cPropPickUpAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataPropPickUp::HandleAttributeData(*this, packet);
    }

    const char *cPropPickUpAnimationProfile::RetClassName() const
    {
        return "cPropPickUpAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cPropPickUpAnimationProfileRegistrar(
        "cPropPickUpAnimationProfile", cPropPickUpAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x8250CA40: the class factory.
    RWS::CAttributeHandler *cPropPickUpAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cPropPickUpAnimationProfile;
    }
}
