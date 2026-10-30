#include "CHARACTER/cCwGoliathCharacterWrapper.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *cCwGoliathCharacterWrapper::RetClassName() const
    {
        return "cCwGoliathCharacterWrapper";
    }
}

namespace CHARACTER
{
    static RWS::CClassFactory::CRegistrar cCwGoliathCharacterWrapperRegistrar(
        "cCwGoliathCharacterWrapper", cCwGoliathCharacterWrapper::MakeNew, 0x34C0, false);
}
