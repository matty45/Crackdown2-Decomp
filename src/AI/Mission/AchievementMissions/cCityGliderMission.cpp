#include "AI/cCityGliderMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cCityGliderMission::ms_pcCityGliderMissionClass = 0;

    cCityGliderMission::cCityGliderMission() {}

    const Fun_Runtime::cClass &cCityGliderMission::RetClass() const
    {
        return *ms_pcCityGliderMissionClass;
    }

    const char *cCityGliderMission::RetClassName() const
    {
        return "cCityGliderMission";
    }

    bool cCityGliderMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcCityGliderMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cCityGliderMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCityGliderMission();
    }
}

static RWS::CClassFactory::CRegistrar cCityGliderMissionRegistrar(
    "cCityGliderMission", AI::cCityGliderMission::MakeNew, 0x440, false);
