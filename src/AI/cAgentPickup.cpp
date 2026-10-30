#include "AI/cAgentPickup.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cAgentPickup::ms_pcAgentPickupClass = 0;

    cAgentPickup::cAgentPickup() {}

    const Fun_Runtime::cClass &cAgentPickup::RetClass() const
    {
        return *ms_pcAgentPickupClass;
    }

    const char *cAgentPickup::RetClassName() const
    {
        return "cAgentPickup";
    }

    bool cAgentPickup::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAgentPickupClass->IsA(c);
    }

    RWS::CAttributeHandler *cAgentPickup::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAgentPickup();
    }
}

static RWS::CClassFactory::CRegistrar cAgentPickupRegistrar(
    "cAgentPickup", AI::cAgentPickup::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar cAgentPickupRegistrar(
        "cAgentPickup", cAgentPickup::MakeNew, 0x140, false);
}
