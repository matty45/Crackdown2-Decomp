#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cPropDropAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cPropDropAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataPropDrop::HandleAttributeData(*this, packet);
    }

    const char *cPropDropAnimationProfile::RetClassName() const
    {
        return "cPropDropAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cPropDropAnimationProfileRegistrar(
        "cPropDropAnimationProfile", cPropDropAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x8250C270: the class factory.
    RWS::CAttributeHandler *cPropDropAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cPropDropAnimationProfile;
    }
}
