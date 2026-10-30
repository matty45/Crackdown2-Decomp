#include "AI/cTrainingHeliPilot.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cTrainingHeliPilot::ms_pcTrainingHeliPilotClass = 0;

    cTrainingHeliPilot::cTrainingHeliPilot() {}

    const Fun_Runtime::cClass &cTrainingHeliPilot::RetClass() const
    {
        return *ms_pcTrainingHeliPilotClass;
    }

    const char *cTrainingHeliPilot::RetClassName() const
    {
        return "cTrainingHeliPilot";
    }

    bool cTrainingHeliPilot::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcTrainingHeliPilotClass->IsA(c);
    }

    RWS::CAttributeHandler *cTrainingHeliPilot::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTrainingHeliPilot();
    }
}

static RWS::CClassFactory::CRegistrar cTrainingHeliPilotRegistrar(
    "cTrainingHeliPilot", AI::cTrainingHeliPilot::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar cTrainingHeliPilotRegistrar(
        "cTrainingHeliPilot", cTrainingHeliPilot::MakeNew, 0x150, false);
}
