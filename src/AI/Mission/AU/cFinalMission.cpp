#include "AI/cFinalMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cFinalMission::ms_pcFinalMissionClass = 0;

    cFinalMission::cFinalMission() {}

    const Fun_Runtime::cClass &cFinalMission::RetClass() const
    {
        return *ms_pcFinalMissionClass;
    }

    const char *cFinalMission::RetClassName() const
    {
        return "cFinalMission";
    }

    bool cFinalMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcFinalMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cFinalMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cFinalMission();
    }
}

static RWS::CClassFactory::CRegistrar cFinalMissionRegistrar(
    "cFinalMission", AI::cFinalMission::MakeNew, 0x7C, false);
