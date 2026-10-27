#include "AI/cPKDropPilot.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cPKDropPilot::ms_pcPKDropPilotClass = 0;

    cPKDropPilot::cPKDropPilot() {}

    const Fun_Runtime::cClass &cPKDropPilot::RetClass() const
    {
        return *ms_pcPKDropPilotClass;
    }

    const char *cPKDropPilot::RetClassName() const
    {
        return "cPKDropPilot";
    }

    bool cPKDropPilot::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcPKDropPilotClass->IsA(c);
    }

    RWS::CAttributeHandler *cPKDropPilot::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cPKDropPilot();
    }
}

static RWS::CClassFactory::CRegistrar cPKDropPilotRegistrar(
    "cPKDropPilot", AI::cPKDropPilot::MakeNew, 0x7C, false);
