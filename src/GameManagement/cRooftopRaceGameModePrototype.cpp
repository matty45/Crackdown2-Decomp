#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "GameManagement/cRooftopRaceGameModePrototype.h"

namespace GameManagement
{
    RWS::CAttributeHandler *cRooftopRaceGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cRooftopRaceGameModePrototype;
    }

    const char *cRooftopRaceGameModePrototype::RetClassName() const
    {
        return "cRooftopRaceGameModePrototype";
    }

    int cRooftopRaceGameModePrototype::RetStringID() const
    {
        return 0x1A2CF73E;
    }

    static RWS::CClassFactory::CRegistrar cRooftopRaceGameModePrototypeRegistrar(
        "cRooftopRaceGameModePrototype", cRooftopRaceGameModePrototype::MakeNew, 0x148, false);
}
