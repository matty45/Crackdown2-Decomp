// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "GameManagement/cGameModeVFXProfile.h"
#include "cd2/memory.h"

namespace GameManagement
{
    int cGameModeVFXProfile::m_aVFXID[13];

    RWS::CAttributeHandler *cGameModeVFXProfile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cGameModeVFXProfile(packet);
    }

    const char *cGameModeVFXProfile::RetClassName() const
    {
        return "cGameModeVFXProfile";
    }

    static RWS::CClassFactory::CRegistrar cGameModeVFXProfileRegistrar(
        "cGameModeVFXProfile", cGameModeVFXProfile::MakeNew, 0x18, false);
}
