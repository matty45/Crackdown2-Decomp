#include "AI/cBasePatrolRouteEvent.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cBasePatrolRouteEvent::ms_pcBasePatrolRouteEventClass = 0;

    cBasePatrolRouteEvent::cBasePatrolRouteEvent() {}

    const Fun_Runtime::cClass &cBasePatrolRouteEvent::RetClass() const
    {
        return *ms_pcBasePatrolRouteEventClass;
    }

    const char *cBasePatrolRouteEvent::RetClassName() const
    {
        return "cBasePatrolRouteEvent";
    }

    bool cBasePatrolRouteEvent::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcBasePatrolRouteEventClass->IsA(c);
    }

    RWS::CAttributeHandler *cBasePatrolRouteEvent::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cBasePatrolRouteEvent();
    }
}

static RWS::CClassFactory::CRegistrar cBasePatrolRouteEventRegistrar(
    "cBasePatrolRouteEvent", AI::cBasePatrolRouteEvent::MakeNew, 0x90, false);
