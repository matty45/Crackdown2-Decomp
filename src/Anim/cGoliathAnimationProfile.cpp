#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cGoliathAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cGoliathAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataGoliath::HandleAttributeData(*this, packet);
    }

    const char *cGoliathAnimationProfile::RetClassName() const
    {
        return "cGoliathAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cGoliathAnimationProfileRegistrar(
        "cGoliathAnimationProfile", cGoliathAnimationProfile::MakeNew, 0x4C, false);

    // CD2 0x824ECF80: the class factory.
    RWS::CAttributeHandler *cGoliathAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGoliathAnimationProfile;
    }
}
