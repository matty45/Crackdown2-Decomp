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

#include "cd2/memory.h"

// CD2 0x8287B300: the class-factory constructor; the constructor stays out of line.
namespace unknown
{
    RWS::CAttributeHandler *cATVAssaultGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cATVAssaultGameModePrototype;
    }
}
