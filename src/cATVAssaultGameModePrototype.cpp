#include "rws/classfactory.h"
#include "unknown/cATVAssaultGameModePrototype.h"

namespace unknown
{
    const char *cATVAssaultGameModePrototype::RetClassName() const
    {
        return "cATVAssaultGameModePrototype";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cATVAssaultGameModePrototypeRegistrar(
        "cATVAssaultGameModePrototype", cATVAssaultGameModePrototype::MakeNew, 0x260, false);
}
