// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "unknown/cRenegadesGameModePrototype.h"
#include "cd2/memory.h"

namespace unknown
{
    const char *cRenegadesGameModePrototype::RetClassName() const
    {
        return "cRenegadesGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cRenegadesGameModePrototypeRegistrar(
        "cRenegadesGameModePrototype", cRenegadesGameModePrototype::MakeNew, 0x1e8, false);

    // CD2 0x82875328: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cRenegadesGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cRenegadesGameModePrototype;
    }
}
