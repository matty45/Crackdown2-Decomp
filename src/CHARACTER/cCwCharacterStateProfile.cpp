#include "CHARACTER/cCwCharacterStateProfile.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *cCwCharacterStateProfile::RetClassName() const
    {
        return "cCwCharacterStateProfile";
    }
}

namespace CHARACTER
{
    static RWS::CClassFactory::CRegistrar cCwCharacterStateProfileRegistrar(
        "cCwCharacterStateProfile", cCwCharacterStateProfile::MakeNew, 0xCC, false);
}
