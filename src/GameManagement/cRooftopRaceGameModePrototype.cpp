#include "rws/classfactory.h"
#include "GameManagement/cRooftopRaceGameModePrototype.h"

namespace GameManagement
{
    const char *cRooftopRaceGameModePrototype::RetClassName() const
    {
        return "cRooftopRaceGameModePrototype";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cRooftopRaceGameModePrototypeRegistrar(
        "cRooftopRaceGameModePrototype", cRooftopRaceGameModePrototype::MakeNew, 0x148, false);
}
