#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "CHARACTER/cCwCharacter.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace CHARACTER
{
    const char *cCwCharacter::RetClassName() const
    {
        return "cCwCharacter";
    }

    static RWS::CClassFactory::CRegistrar cCwCharacterRegistrar(
        "cCwCharacter", cCwCharacter::MakeNew, 0x2CE0, false);

    // CD2 0x8253F438: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cCwCharacter::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCwCharacter(packet);
    }
}
