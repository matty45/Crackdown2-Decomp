#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Anim/cPropThrowNPCAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cPropThrowNPCAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataPropThrowNPC::HandleAttributeData(*this, packet);
    }

    const char *cPropThrowNPCAnimationProfile::RetClassName() const
    {
        return "cPropThrowNPCAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cPropThrowNPCAnimationProfileRegistrar(
        "cPropThrowNPCAnimationProfile", cPropThrowNPCAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x824EBE98: the class factory.
    RWS::CAttributeHandler *cPropThrowNPCAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cPropThrowNPCAnimationProfile;
    }
}
