#include "rws/classfactory.h"
#include "unknown/cTeamATVAssaultGameModePrototype.h"

namespace unknown
{
    const char *cTeamATVAssaultGameModePrototype::RetClassName() const
    {
        return "cTeamATVAssaultGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cTeamATVAssaultGameModePrototypeRegistrar(
        "cTeamATVAssaultGameModePrototype", cTeamATVAssaultGameModePrototype::MakeNew, 0x260, false);
}
