#include "AI/cAgencyTowerSegmentMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cAgencyTowerSegmentMission::ms_pcAgencyTowerSegmentMissionClass = 0;

    cAgencyTowerSegmentMission::cAgencyTowerSegmentMission() {}

    const Fun_Runtime::cClass &cAgencyTowerSegmentMission::RetClass() const
    {
        return *ms_pcAgencyTowerSegmentMissionClass;
    }

    const char *cAgencyTowerSegmentMission::RetClassName() const
    {
        return "cAgencyTowerSegmentMission";
    }

    bool cAgencyTowerSegmentMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAgencyTowerSegmentMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cAgencyTowerSegmentMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAgencyTowerSegmentMission();
    }
}

static RWS::CClassFactory::CRegistrar cAgencyTowerSegmentMissionRegistrar(
    "cAgencyTowerSegmentMission", AI::cAgencyTowerSegmentMission::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar cAgencyTowerSegmentMissionRegistrar(
        "cAgencyTowerSegmentMission", cAgencyTowerSegmentMission::MakeNew, 0x710, false);
}
