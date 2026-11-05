#include "rws/classfactory.h"
#include "unknown/cKeysToTheCityGameModePrototype.h"

namespace unknown
{
    const char *cKeysToTheCityGameModePrototype::RetClassName() const
    {
        return "cKeysToTheCityGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cKeysToTheCityGameModePrototypeRegistrar(
        "cKeysToTheCityGameModePrototype", cKeysToTheCityGameModePrototype::MakeNew, 0x120, false);
}
