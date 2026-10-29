#include "AI/BreachPilot.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *BreachPilot::ms_pBreachPilotClass = 0;

    BreachPilot::BreachPilot() {}

    const Fun_Runtime::cClass &BreachPilot::RetClass() const
    {
        return *ms_pBreachPilotClass;
    }

    const char *BreachPilot::RetClassName() const
    {
        return "BreachPilot";
    }

    bool BreachPilot::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pBreachPilotClass->IsA(c);
    }

    RWS::CAttributeHandler *BreachPilot::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new BreachPilot();
    }
}

static RWS::CClassFactory::CRegistrar BreachPilotRegistrar(
    "BreachPilot", AI::BreachPilot::MakeNew, 0x7C, false);
