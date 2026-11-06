#include "rws/classfactory.h"
#include "unknown/cATVAssaultGameModePrototype.h"
#include "cd2/memory.h"

namespace unknown
{
    const char *cATVAssaultGameModePrototype::RetClassName() const
    {
        return "cATVAssaultGameModePrototype";
    }

    int cATVAssaultGameModePrototype::RetStringID() const
    {
        return 0x77E10144;
    }

    static RWS::CClassFactory::CRegistrar cATVAssaultGameModePrototypeRegistrar(
        "cATVAssaultGameModePrototype", cATVAssaultGameModePrototype::MakeNew, 0x260, false);

    // CD2 0x8287B300: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cATVAssaultGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cATVAssaultGameModePrototype;
    }
}
