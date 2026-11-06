// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cBaseJumperMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cBaseJumperMission::ms_pcBaseJumperMissionClass = 0;

    cBaseJumperMission::cBaseJumperMission() {}

    const Fun_Runtime::cClass &cBaseJumperMission::RetClass() const
    {
        return *ms_pcBaseJumperMissionClass;
    }

    const char *cBaseJumperMission::RetClassName() const
    {
        return "cBaseJumperMission";
    }

    bool cBaseJumperMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcBaseJumperMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cBaseJumperMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cBaseJumperMission();
    }
}

static RWS::CClassFactory::CRegistrar cBaseJumperMissionRegistrar(
    "cBaseJumperMission", AI::cBaseJumperMission::MakeNew, 0x400, false);
