#include "rws/classfactory.h"
#include "GameManagement/cRooftopRaceGameModePrototype.h"

namespace GameManagement
{
    const char *cRooftopRaceGameModePrototype::RetClassName() const
    {
        return "cRooftopRaceGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cRooftopRaceGameModePrototypeRegistrar(
        "cRooftopRaceGameModePrototype", cRooftopRaceGameModePrototype::MakeNew, 0x148, false);
}
