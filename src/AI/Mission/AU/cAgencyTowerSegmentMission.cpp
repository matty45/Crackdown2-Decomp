
// The surviving singleton accessor is folded into this split. CD2's world-manager
// constructor 0x82278B80 stores this in the global read by 0x8245C8A8.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cAgencyTowerSegmentMission.h"
#include "rws/classfactory.h"
#include "WorldManager/cWorldManager.h"
#include "cd2/memory.h"

namespace WorldManager
{
    cWorldManager *cWorldManager::RetInstance()
    {
        return ms_pInstance;
    }
}

namespace AI
{
    const Fun_Runtime::cClass *cAgencyTowerSegmentMission::ms_pcAgencyTowerSegmentMissionClass = &cAgencyTowerSegmentMission::StaticCreateClass();

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

    static RWS::CClassFactory::CRegistrar cAgencyTowerSegmentMissionRegistrar(
        "cAgencyTowerSegmentMission", cAgencyTowerSegmentMission::MakeNew, 0x710, false);

    Fun_Runtime::cClass &cAgencyTowerSegmentMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgencyTowerSegmentMissionClass = new Fun_Runtime::cClass(0x2104E, "cAgencyTowerSegmentMission", 0x710);
        return *cAgencyTowerSegmentMissionClass;
    }

    // CD2 0x82F88028: runtime mission inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAgencyTowerSegmentMissioncMissionInheritRegistrar(
        AI::cAgencyTowerSegmentMission::StaticCreateClass(), AI::cMission::StaticCreateClass());
}
