// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "GameManagement/cGameModeStartZone.h"
#include "cd2/memory.h"

namespace GameManagement
{
    // CD2 0x828821E0: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cGameModeStartZone::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGameModeStartZone;
    }

    const char *cGameModeStartZone::RetClassName() const
    {
        return "cGameModeStartZone";
    }

    cGameModePrototype *cGameModeStartZone::RetGameModePrototype() const
    {
        return m_pGameModePrototype;
    }

    unsigned char cGameModeStartZone::RetMinimumAgilityLevel() const
    {
        return m_nMinimumAgilityLevel;
    }

    unsigned char cGameModeStartZone::RetMinNumParticipants() const
    {
        return m_nMinNumParticipants;
    }

    unsigned char cGameModeStartZone::RetMaxNumParticipants() const
    {
        return m_nMaxNumParticipants;
    }

    unsigned int cGameModeStartZone::GetNumObjectIDBits() const
    {
        return 32;
    }

    static RWS::CClassFactory::CRegistrar cGameModeStartZoneRegistrar(
        "cGameModeStartZone", cGameModeStartZone::MakeNew, 0x3d0, false);


}
