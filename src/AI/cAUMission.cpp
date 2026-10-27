#include "AI/cAUMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cAUMission::ms_pcAUMissionClass = 0;

    cAUMission::cAUMission() {}

    const Fun_Runtime::cClass &cAUMission::RetClass() const
    {
        return *ms_pcAUMissionClass;
    }

    const char *cAUMission::RetClassName() const
    {
        return "cAUMission";
    }

    bool cAUMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAUMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cAUMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAUMission();
    }
}

static RWS::CClassFactory::CRegistrar cAUMissionRegistrar(
    "cAUMission", AI::cAUMission::MakeNew, 0x7C, false);
