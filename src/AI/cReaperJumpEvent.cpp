#include "AI/cReaperJumpEvent.h"
#include "AI/cReaperPropAttackEvent.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cReaperJumpEvent::ms_pcReaperJumpEventClass = &cReaperJumpEvent::StaticCreateClass();

    const Fun_Runtime::cClass &cReaperJumpEvent::RetClass() const
    {
        return *ms_pcReaperJumpEventClass;
    }

    bool cReaperJumpEvent::IsA(const Fun_Runtime::cClass &testClass) const
    {
        return ms_pcReaperJumpEventClass->IsA(testClass);
    }

    const char *cReaperJumpEvent::RetClassName() const
    {
        return "cReaperJumpEvent";
    }

    RWS::CAttributeHandler *cReaperJumpEvent::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cReaperJumpEvent;
    }

    static RWS::CClassFactory::CRegistrar cReaperJumpEventRegistrar(
        "cReaperJumpEvent", cReaperJumpEvent::MakeNew, 0x90, false);

    const Fun_Runtime::cClass *cReaperPropAttackEvent::ms_pcReaperPropAttackEventClass = &cReaperPropAttackEvent::StaticCreateClass();

    const Fun_Runtime::cClass &cReaperPropAttackEvent::RetClass() const
    {
        return *ms_pcReaperPropAttackEventClass;
    }

    bool cReaperPropAttackEvent::IsA(const Fun_Runtime::cClass &testClass) const
    {
        return ms_pcReaperPropAttackEventClass->IsA(testClass);
    }

    const char *cReaperPropAttackEvent::RetClassName() const
    {
        return "cReaperPropAttackEvent";
    }

    RWS::CAttributeHandler *cReaperPropAttackEvent::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cReaperPropAttackEvent;
    }

    static RWS::CClassFactory::CRegistrar cReaperPropAttackEventRegistrar(
        "cReaperPropAttackEvent", cReaperPropAttackEvent::MakeNew, 0x90, false);

}
