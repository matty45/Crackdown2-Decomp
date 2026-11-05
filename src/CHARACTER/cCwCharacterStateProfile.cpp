#include "fun_runtime/retval.h"
#include "CHARACTER/cCwCharacterStateProfile.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *cCwCharacterStateProfile::RetClassName() const
    {
        return "cCwCharacterStateProfile";
    }

    const char *cCwCharacterStateProfile::RetCharacterStates() const
    {
        return "eCharacterStates";
    }

    static RWS::CClassFactory::CRegistrar cCwCharacterStateProfileRegistrar(
        "cCwCharacterStateProfile", cCwCharacterStateProfile::MakeNew, 0xCC, false);

    Fun_Runtime::RetVal cCwCharacterStateProfile::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
