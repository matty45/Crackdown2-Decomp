// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cBeaconMission.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace AI
{
    const Fun_Runtime::cClass *cBeaconMission::ms_pcBeaconMissionClass = &cBeaconMission::StaticCreateClass();

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

    void cBeaconMission::NotifySquadDead(Activity::cSquadSpawnPoint *)
    {
        ++m_nNumInitialSquadsDead;
    }

    RWS::CAttributeHandler *cBeaconMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cBeaconMission();
    }
}

static RWS::CClassFactory::CRegistrar cBeaconMissionRegistrar(
    "cBeaconMission", AI::cBeaconMission::MakeNew, 0x2300, false);

namespace AI
{
    Fun_Runtime::cClass &cBeaconMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cBeaconMissionClass = new Fun_Runtime::cClass(0x205C3, "cBeaconMission", 0x2300);
        return *cBeaconMissionClass;
    }

    // CD2 0x82F88C20: runtime mission inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cBeaconMissioncMissionInheritRegistrar(
        AI::cBeaconMission::StaticCreateClass(), AI::cMission::StaticCreateClass());
}
