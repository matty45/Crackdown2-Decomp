#include "GameManagement/cCHordeArena.h"
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
