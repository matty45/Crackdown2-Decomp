// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "ZoneManager/cReverbZone.h"
#include "cd2/memory.h"
#include "PLAYER/cPlayer.h"
#include "Audio/cReverbControl.h"

namespace ZoneManager
{
    RWS::CAttributeHandler *cReverbZone::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cReverbZone(packet);
    }

    const char *cReverbZone::RetClassName() const
    {
        return "cReverbZone";
    }

    cReverbZone::~cReverbZone()
    {
    }

    // CD2's ambience-zone table holds this copy too (identical bodies folded).
    void cReverbZone::TermTriggerZone()
    {
        cPlayerTriggerZone::TermTriggerZone();
    }

    void cReverbZone::OnPlayerLeave(CHARACTER::cCharacter *pCharacter)
    {
        if (pCharacter == PLAYER::cPlayer::RetLocalPlayerCharacter())
        {
            Audio::cReverbControl::Exit(m_nLayerType);
            m_bPreviouslyLeft = true;
        }
    }

    static RWS::CClassFactory::CRegistrar cReverbZoneRegistrar(
        "cReverbZone", cReverbZone::MakeNew, 0x150, false);
}
