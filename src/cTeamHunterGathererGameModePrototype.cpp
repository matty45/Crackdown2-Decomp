#include "rws/classfactory.h"
#include "unknown/cTeamHunterGathererGameModePrototype.h"

namespace unknown
{
    const char *cTeamHunterGathererGameModePrototype::RetClassName() const
    {
        return "cTeamHunterGathererGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cTeamHunterGathererGameModePrototypeRegistrar(
        "cTeamHunterGathererGameModePrototype", cTeamHunterGathererGameModePrototype::MakeNew, 0x198, false);
}
