#include "GameManagement/cCHordeArena.h"
// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"

namespace GameManagement
{
    const char *cCHordeArena::RetClassName() const
    {
        return "cCHordeArena";
    }

    RWS::CAttributeHandler *cCHordeArena::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCHordeArena();
    }
}

static RWS::CClassFactory::CRegistrar cCHordeArenaRegistrar(
    "cCHordeArena", GameManagement::cCHordeArena::MakeNew, 0x110, false);
