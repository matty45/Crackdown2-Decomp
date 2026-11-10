// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "GameManagement/cTagGameModePrototype.h"
#include "cd2/memory.h"

namespace GameManagement
{
    RWS::CAttributeHandler *cTagGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cTagGameModePrototype;
    }

    const char *cTagGameModePrototype::RetClassName() const
    {
        return "cTagGameModePrototype";
    }

    int cTagGameModePrototype::RetStringID() const
    {
        return 0xB993343F;
    }

    static RWS::CClassFactory::CRegistrar cTagGameModePrototypeRegistrar(
        "cTagGameModePrototype", cTagGameModePrototype::MakeNew, 0x1d8, false);
}
