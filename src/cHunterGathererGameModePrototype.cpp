#include "rws/classfactory.h"
#include "unknown/cHunterGathererGameModePrototype.h"
#include "cd2/memory.h"

namespace unknown
{
    const char *cHunterGathererGameModePrototype::RetClassName() const
    {
        return "cHunterGathererGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cHunterGathererGameModePrototypeRegistrar(
        "cHunterGathererGameModePrototype", cHunterGathererGameModePrototype::MakeNew, 0x198, false);

    // CD2 0x8287E1E8: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cHunterGathererGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cHunterGathererGameModePrototype;
    }
}
