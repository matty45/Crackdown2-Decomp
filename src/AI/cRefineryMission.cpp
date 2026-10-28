#include "AI/cRefineryMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cRefineryMission::ms_pcRefineryMissionClass = 0;

    cRefineryMission::cRefineryMission() {}

    const Fun_Runtime::cClass &cRefineryMission::RetClass() const
    {
        return *ms_pcRefineryMissionClass;
    }

    const char *cRefineryMission::RetClassName() const
    {
        return "cRefineryMission";
    }

    bool cRefineryMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcRefineryMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cRefineryMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cRefineryMission();
    }
}

static RWS::CClassFactory::CRegistrar cRefineryMissionRegistrar(
    "cRefineryMission", AI::cRefineryMission::MakeNew, 0x400, false);
