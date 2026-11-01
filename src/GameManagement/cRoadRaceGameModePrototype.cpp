#include "rws/classfactory.h"
#include "GameManagement/cRoadRaceGameModePrototype.h"

namespace GameManagement
{
    const char *cRoadRaceGameModePrototype::RetClassName() const
    {
        return "cRoadRaceGameModePrototype";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cRoadRaceGameModePrototypeRegistrar(
        "cRoadRaceGameModePrototype", cRoadRaceGameModePrototype::MakeNew, 0x148, false);
}
