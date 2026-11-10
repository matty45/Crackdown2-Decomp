// AI/Mission/AchievementMissions/cPebbleDashMission.cpp: RuffKing's Libraries/Shared/AI/Mission/AchievementMissions/cPebbleDashMission.cpp.
// Its text range and the evidence for it are in config/splits.txt; its own functions are not written yet.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "AI/cLocalPlayerTrigger.h"
#include "AI/cPebbleDashMission.h"
#include "cd2/memory.h"

namespace AI
{
    RWS::CAttributeHandler *cLocalPlayerTrigger::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cLocalPlayerTrigger(packet);
    }

    const char *cLocalPlayerTrigger::RetClassName() const
    {
        return "cLocalPlayerTrigger";
    }

    cLocalPlayerTrigger::cLocalPlayerTrigger(const RWS::CAttributePacket &packet)
        : cPlayerTriggerZone(false), m_nTriggerFlags(0)
    {
        m_EventHandler.Register(this, packet.GetInstanceId());
        InitTriggerZone();
    }

    cLocalPlayerTrigger::~cLocalPlayerTrigger() {}

    static RWS::CClassFactory::CRegistrar cLocalPlayerTriggerRegistrar(
        "cLocalPlayerTrigger", cLocalPlayerTrigger::MakeNew, 0x100, false);

    static RWS::CClassFactory::CRegistrar cPebbleDashMissionRegistrar(
        "cPebbleDashMission", cPebbleDashMission::MakeNew, 0x3D0, false);
}
