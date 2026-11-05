#include "rws/classfactory.h"
#include "GameManagement/cTagGameModePrototype.h"

namespace GameManagement
{
    const char *cTagGameModePrototype::RetClassName() const
    {
        return "cTagGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cTagGameModePrototypeRegistrar(
        "cTagGameModePrototype", cTagGameModePrototype::MakeNew, 0x1d8, false);
}
