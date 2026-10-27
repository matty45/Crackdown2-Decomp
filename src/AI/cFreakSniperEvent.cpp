#include "AI/cFreakSniperEvent.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cFreakSniperEvent::ms_pcFreakSniperEventClass = 0;

    cFreakSniperEvent::cFreakSniperEvent() {}

    const Fun_Runtime::cClass &cFreakSniperEvent::RetClass() const
    {
        return *ms_pcFreakSniperEventClass;
    }

    const char *cFreakSniperEvent::RetClassName() const
    {
        return "cFreakSniperEvent";
    }

    bool cFreakSniperEvent::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcFreakSniperEventClass->IsA(c);
    }

    RWS::CAttributeHandler *cFreakSniperEvent::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cFreakSniperEvent();
    }
}

static RWS::CClassFactory::CRegistrar cFreakSniperEventRegistrar(
    "cFreakSniperEvent", AI::cFreakSniperEvent::MakeNew, 0x7C, false);
