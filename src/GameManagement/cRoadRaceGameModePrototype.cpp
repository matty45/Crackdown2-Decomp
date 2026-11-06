#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "GameManagement/cRoadRaceGameModePrototype.h"

namespace GameManagement
{
    RWS::CAttributeHandler *cRoadRaceGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cRoadRaceGameModePrototype;
    }

    const char *cRoadRaceGameModePrototype::RetClassName() const
    {
        return "cRoadRaceGameModePrototype";
    }

    int cRoadRaceGameModePrototype::RetStringID() const
    {
        return 0x5A6B21DC;
    }

    static RWS::CClassFactory::CRegistrar cRoadRaceGameModePrototypeRegistrar(
        "cRoadRaceGameModePrototype", cRoadRaceGameModePrototype::MakeNew, 0x148, false);
}
