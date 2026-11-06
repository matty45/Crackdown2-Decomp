// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cAUMission.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace AI
{
    const Fun_Runtime::cClass *cAUMission::ms_pcAUMissionClass = &cAUMission::StaticCreateClass();

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
    "cAUMission", AI::cAUMission::MakeNew, 0x5F0, false);

namespace AI
{
    Fun_Runtime::cClass &cAUMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAUMissionClass = new Fun_Runtime::cClass(0x205C2, "cAUMission", 0x5F0);
        return *cAUMissionClass;
    }

    // CD2 0x82F88418: runtime mission inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAUMissioncMissionInheritRegistrar(
        AI::cAUMission::StaticCreateClass(), AI::cMission::StaticCreateClass());
}
