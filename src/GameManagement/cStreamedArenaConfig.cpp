#include "rws/classfactory.h"
#include "GameManagement/cStreamedArenaConfig.h"

namespace GameManagement
{
    const char *cStreamedArenaConfig::RetClassName() const
    {
        return "cStreamedArenaConfig";
    }

    static RWS::CClassFactory::CRegistrar cStreamedArenaConfigRegistrar(
        "cStreamedArenaConfig", cStreamedArenaConfig::MakeNew, 0x28, false);
}
