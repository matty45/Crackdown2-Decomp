#include "GangManager/cGangInfoPrototype.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace GangManager
{
    const char *cGangInfoPrototype::RetClassName() const
    {
        return "cGangInfoPrototype";
    }

    static RWS::CClassFactory::CRegistrar cGangInfoPrototypeRegistrar(
        "cGangInfoPrototype", cGangInfoPrototype::MakeNew, 0xD0, false);

    // CD2 0x82676D60: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cGangInfoPrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGangInfoPrototype;
    }
}
