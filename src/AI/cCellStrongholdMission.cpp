#include "AI/cCellStrongholdMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cCellStrongholdMission::ms_pcCellStrongholdMissionClass = 0;

    cCellStrongholdMission::cCellStrongholdMission() {}

    const Fun_Runtime::cClass &cCellStrongholdMission::RetClass() const
    {
        return *ms_pcCellStrongholdMissionClass;
    }

    const char *cCellStrongholdMission::RetClassName() const
    {
        return "cCellStrongholdMission";
    }

    bool cCellStrongholdMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcCellStrongholdMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cCellStrongholdMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCellStrongholdMission();
    }
}

static RWS::CClassFactory::CRegistrar cCellStrongholdMissionRegistrar(
    "cCellStrongholdMission", AI::cCellStrongholdMission::MakeNew, 0x7C, false);
