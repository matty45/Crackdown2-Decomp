#include "Anim/cEquipmentThrowNPCFullAnimationProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    void cEquipmentThrowNPCFullAnimationProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cSpecificAnimationProfile::HandleAttributes(packet);
        cProfileDataEquipmentThrowNPCFull::HandleAttributeData(*this, packet);
    }

    const char *cEquipmentThrowNPCFullAnimationProfile::RetClassName() const
    {
        return "cEquipmentThrowNPCFullAnimationProfile";
    }

    static RWS::CClassFactory::CRegistrar cEquipmentThrowNPCFullAnimationProfileRegistrar(
        "cEquipmentThrowNPCFullAnimationProfile", cEquipmentThrowNPCFullAnimationProfile::MakeNew, 0x40, false);

    // CD2 0x824EB4F8: the class factory.
    RWS::CAttributeHandler *cEquipmentThrowNPCFullAnimationProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cEquipmentThrowNPCFullAnimationProfile;
    }
}
