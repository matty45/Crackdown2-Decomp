// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "unknown/cATVAssaultGameModePrototype.h"
#include "cd2/memory.h"

namespace unknown
{
    const char *cATVAssaultGameModePrototype::RetClassName() const
    {
        return "cATVAssaultGameModePrototype";
    }

    int cATVAssaultGameModePrototype::RetStringID() const
    {
        return 0x77E10144;
    }

    static RWS::CClassFactory::CRegistrar cATVAssaultGameModePrototypeRegistrar(
        "cATVAssaultGameModePrototype", cATVAssaultGameModePrototype::MakeNew, 0x260, false);

    // CD2 0x8287B300: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cATVAssaultGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cATVAssaultGameModePrototype;
    }
}
