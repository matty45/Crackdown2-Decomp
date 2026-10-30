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
