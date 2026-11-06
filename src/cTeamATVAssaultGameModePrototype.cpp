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
