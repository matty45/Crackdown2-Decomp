#include "AI/cReaperJumpEvent.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cReaperJumpEvent::ms_pcReaperJumpEventClass = 0;

    cReaperJumpEvent::cReaperJumpEvent() {}

    const Fun_Runtime::cClass &cReaperJumpEvent::RetClass() const
    {
        return *ms_pcReaperJumpEventClass;
    }

    const char *cReaperJumpEvent::RetClassName() const
    {
        return "cReaperJumpEvent";
    }

    bool cReaperJumpEvent::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcReaperJumpEventClass->IsA(c);
    }

    RWS::CAttributeHandler *cReaperJumpEvent::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cReaperJumpEvent();
    }
}

static RWS::CClassFactory::CRegistrar cReaperJumpEventRegistrar(
    "cReaperJumpEvent", AI::cReaperJumpEvent::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar cReaperJumpEventRegistrar(
        "cReaperJumpEvent", cReaperJumpEvent::MakeNew, 0x90, false);
}
