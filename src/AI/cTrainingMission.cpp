#include "AI/cTrainingMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cTrainingMission::ms_pcTrainingMissionClass = 0;

    cTrainingMission::cTrainingMission() {}

    const Fun_Runtime::cClass &cTrainingMission::RetClass() const
    {
        return *ms_pcTrainingMissionClass;
    }

    const char *cTrainingMission::RetClassName() const
    {
        return "cTrainingMission";
    }

    bool cTrainingMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcTrainingMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cTrainingMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTrainingMission();
    }
}

static RWS::CClassFactory::CRegistrar cTrainingMissionRegistrar(
    "cTrainingMission", AI::cTrainingMission::MakeNew, 0x7C, false);
