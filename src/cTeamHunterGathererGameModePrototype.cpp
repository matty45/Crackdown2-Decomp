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
