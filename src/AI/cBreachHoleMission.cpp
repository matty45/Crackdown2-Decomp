#include "AI/cBreachHoleMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cBreachHoleMission::ms_pcBreachHoleMissionClass = 0;

    cBreachHoleMission::cBreachHoleMission() {}

    const Fun_Runtime::cClass &cBreachHoleMission::RetClass() const
    {
        return *ms_pcBreachHoleMissionClass;
    }

    const char *cBreachHoleMission::RetClassName() const
    {
        return "cBreachHoleMission";
    }

    bool cBreachHoleMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcBreachHoleMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cBreachHoleMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cBreachHoleMission();
    }
}

static RWS::CClassFactory::CRegistrar cBreachHoleMissionRegistrar(
    "cBreachHoleMission", AI::cBreachHoleMission::MakeNew, 0x7C, false);
