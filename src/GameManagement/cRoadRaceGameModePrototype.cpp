#include "rws/classfactory.h"
#include "GameManagement/cRoadRaceGameModePrototype.h"

namespace GameManagement
{
    const char *cRoadRaceGameModePrototype::RetClassName() const
    {
        return "cRoadRaceGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cRoadRaceGameModePrototypeRegistrar(
        "cRoadRaceGameModePrototype", cRoadRaceGameModePrototype::MakeNew, 0x148, false);
}
