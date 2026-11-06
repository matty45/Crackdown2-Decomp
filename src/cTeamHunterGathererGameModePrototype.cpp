#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "unknown/cTeamHunterGathererGameModePrototype.h"

namespace unknown
{
    RWS::CAttributeHandler *cTeamHunterGathererGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cTeamHunterGathererGameModePrototype;
    }

    const char *cTeamHunterGathererGameModePrototype::RetClassName() const
    {
        return "cTeamHunterGathererGameModePrototype";
    }

    int cTeamHunterGathererGameModePrototype::RetStringID() const
    {
        return 0x602ABB49;
    }

    static RWS::CClassFactory::CRegistrar cTeamHunterGathererGameModePrototypeRegistrar(
        "cTeamHunterGathererGameModePrototype", cTeamHunterGathererGameModePrototype::MakeNew, 0x198, false);
}
