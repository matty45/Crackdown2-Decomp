#include "AI/cTrainingRouteEvent.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cTrainingRouteEvent::ms_pcTrainingRouteEventClass = 0;

    cTrainingRouteEvent::cTrainingRouteEvent() {}

    const Fun_Runtime::cClass &cTrainingRouteEvent::RetClass() const
    {
        return *ms_pcTrainingRouteEventClass;
    }

    const char *cTrainingRouteEvent::RetClassName() const
    {
        return "cTrainingRouteEvent";
    }

    bool cTrainingRouteEvent::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcTrainingRouteEventClass->IsA(c);
    }

    RWS::CAttributeHandler *cTrainingRouteEvent::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTrainingRouteEvent();
    }
}

static RWS::CClassFactory::CRegistrar cTrainingRouteEventRegistrar(
    "cTrainingRouteEvent", AI::cTrainingRouteEvent::MakeNew, 0x7C, false);
