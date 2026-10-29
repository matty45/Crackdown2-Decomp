#include "AI/cGoliathPatrolRouteEvent.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cGoliathPatrolRouteEvent::ms_pcGoliathPatrolRouteEventClass = 0;

    cGoliathPatrolRouteEvent::cGoliathPatrolRouteEvent() {}

    const Fun_Runtime::cClass &cGoliathPatrolRouteEvent::RetClass() const
    {
        return *ms_pcGoliathPatrolRouteEventClass;
    }

    const char *cGoliathPatrolRouteEvent::RetClassName() const
    {
        return "cGoliathPatrolRouteEvent";
    }

    bool cGoliathPatrolRouteEvent::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcGoliathPatrolRouteEventClass->IsA(c);
    }

    RWS::CAttributeHandler *cGoliathPatrolRouteEvent::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cGoliathPatrolRouteEvent();
    }
}

static RWS::CClassFactory::CRegistrar cGoliathPatrolRouteEventRegistrar(
    "cGoliathPatrolRouteEvent", AI::cGoliathPatrolRouteEvent::MakeNew, 0xA0, false);
