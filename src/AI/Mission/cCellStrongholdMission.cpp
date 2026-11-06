#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cCellStrongholdMission.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace AI
{
    const Fun_Runtime::cClass *cCellStrongholdMission::ms_pcCellStrongholdMissionClass = &cCellStrongholdMission::StaticCreateClass();

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

    static RWS::CClassFactory::CRegistrar cCellStrongholdMissionRegistrar(
        "cCellStrongholdMission", cCellStrongholdMission::MakeNew, 0x410, false);

    Fun_Runtime::cClass &cCellStrongholdMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCellStrongholdMissionClass = new Fun_Runtime::cClass(0x1D97C, "cCellStrongholdMission", 0x410);
        return *cCellStrongholdMissionClass;
    }

    // CD2 0x82F8A870: runtime mission inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cCellStrongholdMissioncMissionInheritRegistrar(
        AI::cCellStrongholdMission::StaticCreateClass(), AI::cMission::StaticCreateClass());
}
