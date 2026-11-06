#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "PLAYER/cPlayer.h"
#include "GameManagement/cMultiPlayerTriggerZone.h"

namespace GameManagement
{
    RWS::CAttributeHandler *cMultiPlayerTriggerZone::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cMultiPlayerTriggerZone(packet);
    }

    const char *cMultiPlayerTriggerZone::RetClassName() const
    {
        return "cMultiPlayerTriggerZone";
    }

    void cMultiPlayerTriggerZone::InitTriggerZone()
    {
        m_bActive = true;
    }

    void cMultiPlayerTriggerZone::TermTriggerZone()
    {
        m_bActive = false;
    }

    bool cMultiPlayerTriggerZone::CanTrigger(PLAYER::cPlayer *player)
    {
        return player->IsAlive();
    }

    static RWS::CClassFactory::CRegistrar cMultiPlayerTriggerZoneRegistrar(
        "cMultiPlayerTriggerZone", cMultiPlayerTriggerZone::MakeNew, 0x70, false);
}
