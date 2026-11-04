#include "CHARACTER/cCwCharacter.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *cCwCharacter::RetClassName() const
    {
        return "cCwCharacter";
    }
}

namespace CHARACTER
{
    static RWS::CClassFactory::CRegistrar cCwCharacterRegistrar(
        "cCwCharacter", cCwCharacter::MakeNew, 0x2CE0, false);
}

#include "cd2/memory.h"

// CD2 0x8253F438: the class-factory constructor; the constructor stays out of line.
namespace CHARACTER
{
    RWS::CAttributeHandler *cCwCharacter::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCwCharacter(packet);
    }
}
