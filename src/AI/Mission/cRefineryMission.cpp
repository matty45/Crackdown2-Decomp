// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cRefineryMission.h"
#include "rws/classfactory.h"
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cRefineryMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cRefineryMissionClass = new Fun_Runtime::cClass(0x404, "cRefineryMission", 0x400);
        return *cRefineryMissionClass;
    }

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

    const Fun_Runtime::cClass *cRefineryMission::ms_pcRefineryMissionClass = &cRefineryMission::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cRefineryMissioncMissionInheritRegistrar(
        cRefineryMission::StaticCreateClass(), cMission::StaticCreateClass());
}

static RWS::CClassFactory::CRegistrar cRefineryMissionRegistrar(
    "cRefineryMission", AI::cRefineryMission::MakeNew, 0x400, false);
