#include "CHARACTER/cGameDamageProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace CHARACTER
{
    RWS::CAttributeHandler *cGameDamageProfile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cGameDamageProfile(packet);
    }

    const char *cGameDamageProfile::RetClassName() const
    {
        return "cGameDamageProfile";
    }

    static RWS::CClassFactory::CRegistrar cGameDamageProfileRegistrar(
        "cGameDamageProfile", cGameDamageProfile::MakeNew, 0x3C, false);
}
