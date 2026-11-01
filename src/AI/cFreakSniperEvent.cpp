#include "AI/cFreakExplodeEvent.h"
#include "AI/cFreakSniperEvent.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cFreakExplodeEvent::ms_pcFreakExplodeEventClass = &cFreakExplodeEvent::StaticCreateClass();

    const Fun_Runtime::cClass &cFreakExplodeEvent::RetClass() const
    {
        return *ms_pcFreakExplodeEventClass;
    }

    bool cFreakExplodeEvent::IsA(const Fun_Runtime::cClass &testClass) const
    {
        return ms_pcFreakExplodeEventClass->IsA(testClass);
    }

    const char *cFreakExplodeEvent::RetClassName() const
    {
        return "cFreakExplodeEvent";
    }

    RWS::CAttributeHandler *cFreakExplodeEvent::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cFreakExplodeEvent;
    }

    static RWS::CClassFactory::CRegistrar cFreakExplodeEventRegistrar(
        "cFreakExplodeEvent", cFreakExplodeEvent::MakeNew, 0x90, false);

    const Fun_Runtime::cClass *cFreakSniperEvent::ms_pcFreakSniperEventClass = &cFreakSniperEvent::StaticCreateClass();

    const Fun_Runtime::cClass &cFreakSniperEvent::RetClass() const
    {
        return *ms_pcFreakSniperEventClass;
    }

    bool cFreakSniperEvent::IsA(const Fun_Runtime::cClass &testClass) const
    {
        return ms_pcFreakSniperEventClass->IsA(testClass);
    }

    const char *cFreakSniperEvent::RetClassName() const
    {
        return "cFreakSniperEvent";
    }

    RWS::CAttributeHandler *cFreakSniperEvent::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cFreakSniperEvent;
    }

    static RWS::CClassFactory::CRegistrar cFreakSniperEventRegistrar(
        "cFreakSniperEvent", cFreakSniperEvent::MakeNew, 0x90, false);

}
