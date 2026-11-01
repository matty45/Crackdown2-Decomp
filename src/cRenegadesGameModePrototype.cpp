#include "rws/classfactory.h"
#include "unknown/cRenegadesGameModePrototype.h"

namespace unknown
{
    const char *cRenegadesGameModePrototype::RetClassName() const
    {
        return "cRenegadesGameModePrototype";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cRenegadesGameModePrototypeRegistrar(
        "cRenegadesGameModePrototype", cRenegadesGameModePrototype::MakeNew, 0x1e8, false);
}
