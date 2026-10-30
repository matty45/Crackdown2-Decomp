#include "AI/cTrainingVOARouteEvent.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cTrainingVOARouteEvent::ms_pcTrainingVOARouteEventClass = 0;

    cTrainingVOARouteEvent::cTrainingVOARouteEvent() {}

    const Fun_Runtime::cClass &cTrainingVOARouteEvent::RetClass() const
    {
        return *ms_pcTrainingVOARouteEventClass;
    }

    const char *cTrainingVOARouteEvent::RetClassName() const
    {
        return "cTrainingVOARouteEvent";
    }

    bool cTrainingVOARouteEvent::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcTrainingVOARouteEventClass->IsA(c);
    }

    RWS::CAttributeHandler *cTrainingVOARouteEvent::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTrainingVOARouteEvent();
    }
}

static RWS::CClassFactory::CRegistrar cTrainingVOARouteEventRegistrar(
    "cTrainingVOARouteEvent", AI::cTrainingVOARouteEvent::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar cTrainingVOARouteEventRegistrar(
        "cTrainingVOARouteEvent", cTrainingVOARouteEvent::MakeNew, 0xA0, false);
}
