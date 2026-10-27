#include "AI/cPilotRespawn.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cPilotRespawn::ms_pcPilotRespawnClass = 0;

    cPilotRespawn::cPilotRespawn() {}

    const Fun_Runtime::cClass &cPilotRespawn::RetClass() const
    {
        return *ms_pcPilotRespawnClass;
    }

    const char *cPilotRespawn::RetClassName() const
    {
        return "cPilotRespawn";
    }

    bool cPilotRespawn::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcPilotRespawnClass->IsA(c);
    }

    RWS::CAttributeHandler *cPilotRespawn::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cPilotRespawn();
    }
}

static RWS::CClassFactory::CRegistrar cPilotRespawnRegistrar(
    "cPilotRespawn", AI::cPilotRespawn::MakeNew, 0x7C, false);
