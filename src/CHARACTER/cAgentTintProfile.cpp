#include "CHARACTER/cAgentTintProfile.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *cAgentTintProfile::RetClassName() const
    {
        return "cAgentTintProfile";
    }

    RWS::CAttributeHandler *cAgentTintProfile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cAgentTintProfile *p = new cAgentTintProfile();
        return p;
    }

    static RWS::CClassFactory::CRegistrar cAgentTintProfileRegistrar(
        "cAgentTintProfile", cAgentTintProfile::MakeNew, 0x18, false);
}
