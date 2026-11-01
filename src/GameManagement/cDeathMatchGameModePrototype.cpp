#include "rws/classfactory.h"
#include "GameManagement/cDeathMatchGameModePrototype.h"

namespace GameManagement
{
    const char *cDeathMatchGameModePrototype::RetClassName() const
    {
        return "cDeathMatchGameModePrototype";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cDeathMatchGameModePrototypeRegistrar(
        "cDeathMatchGameModePrototype", cDeathMatchGameModePrototype::MakeNew, 0x190, false);
}
