#include "rws/classfactory.h"
#include "unknown/cRenegadesGameModePrototype.h"
#include "cd2/memory.h"

namespace unknown
{
    const char *cRenegadesGameModePrototype::RetClassName() const
    {
        return "cRenegadesGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cRenegadesGameModePrototypeRegistrar(
        "cRenegadesGameModePrototype", cRenegadesGameModePrototype::MakeNew, 0x1e8, false);

    // CD2 0x82875328: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cRenegadesGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cRenegadesGameModePrototype;
    }
}
