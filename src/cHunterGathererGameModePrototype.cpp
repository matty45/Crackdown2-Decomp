#include "rws/classfactory.h"
#include "unknown/cHunterGathererGameModePrototype.h"

namespace unknown
{
    const char *cHunterGathererGameModePrototype::RetClassName() const
    {
        return "cHunterGathererGameModePrototype";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cHunterGathererGameModePrototypeRegistrar(
        "cHunterGathererGameModePrototype", cHunterGathererGameModePrototype::MakeNew, 0x198, false);
}
