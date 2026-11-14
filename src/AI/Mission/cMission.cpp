// AI/Mission/cMission.cpp: RuffKing's Libraries/Shared/AI/Mission/cMission.cpp.
// Its text range and the evidence for it are in config/splits.txt; its own functions are not written yet.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cMission.h"
#include "cd2/memory.h"
#include "AI/cSecondaryObjectivesInfo.h"

namespace AI
{
    RWS::CAttributeHandler *cSecondaryObjectivesInfo::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cSecondaryObjectivesInfo;
    }

    const char *cSecondaryObjectivesInfo::RetClassName() const
    {
        return "cSecondaryObjectivesInfo";
    }

    const Fun_Runtime::cClass &cMission::RetClass() const
    {
        return *ms_pcMissionClass;
    }

    RWS::CAttributeHandler *cMission::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cMission;
    }

    const char *cMission::RetClassName() const
    {
        return "cMission";
    }

    Fun_Runtime::cClass &cMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cMissionClass = new Fun_Runtime::cClass(0x403, "cMission", 0x3C0);
        return *cMissionClass;
    }

    void cMission::EnableCompletion()
    {
        if (IsAuthority() && m_eGlobalMissionState == eGMS_Uncompletable)
            SetGlobalMissionState(eGMS_Incomplete, true);
    }
}
