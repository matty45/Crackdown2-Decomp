// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
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
