// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "unknown/cTeamATVAssaultGameModePrototype.h"

namespace unknown
{
    RWS::CAttributeHandler *cTeamATVAssaultGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cTeamATVAssaultGameModePrototype;
    }

    const char *cTeamATVAssaultGameModePrototype::RetClassName() const
    {
        return "cTeamATVAssaultGameModePrototype";
    }

    int cTeamATVAssaultGameModePrototype::RetStringID() const
    {
        return 0x310358CA;
    }

    static RWS::CClassFactory::CRegistrar cTeamATVAssaultGameModePrototypeRegistrar(
        "cTeamATVAssaultGameModePrototype", cTeamATVAssaultGameModePrototype::MakeNew, 0x260, false);
}
