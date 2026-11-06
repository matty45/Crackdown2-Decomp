// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
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
    "cTrainingMission", AI::cTrainingMission::MakeNew, 0x9D0, false);
