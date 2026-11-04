#include "rws/classfactory.h"
#include "unknown/cHunterGathererGameModePrototype.h"

namespace unknown
{
    const char *cHunterGathererGameModePrototype::RetClassName() const
    {
        return "cHunterGathererGameModePrototype";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cHunterGathererGameModePrototypeRegistrar(
        "cHunterGathererGameModePrototype", cHunterGathererGameModePrototype::MakeNew, 0x198, false);
}

#include "cd2/memory.h"

// CD2 0x8287E1E8: the class-factory constructor; the constructor stays out of line.
namespace unknown
{
    RWS::CAttributeHandler *cHunterGathererGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cHunterGathererGameModePrototype;
    }
}
