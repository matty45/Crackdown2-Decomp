#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cCoverAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cCoverAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataCover::HandleAttributeData(*this, packet);
    }

    const char *cCoverAnimationProfile::RetClassName() const
    {
        return "cCoverAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cCoverAnimationProfileRegistrar(
        "cCoverAnimationProfile", cCoverAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x824E7A30: the class factory.
    RWS::CAttributeHandler *cCoverAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCoverAnimationProfile;
    }
}
