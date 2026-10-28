#include "AI/cBeaconMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cBeaconMission::ms_pcBeaconMissionClass = 0;

    cBeaconMission::cBeaconMission() {}

    const Fun_Runtime::cClass &cBeaconMission::RetClass() const
    {
        return *ms_pcBeaconMissionClass;
    }

    const char *cBeaconMission::RetClassName() const
    {
        return "cBeaconMission";
    }

    bool cBeaconMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcBeaconMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cBeaconMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cBeaconMission();
    }
}

static RWS::CClassFactory::CRegistrar cBeaconMissionRegistrar(
    "cBeaconMission", AI::cBeaconMission::MakeNew, 0x2300, false);
