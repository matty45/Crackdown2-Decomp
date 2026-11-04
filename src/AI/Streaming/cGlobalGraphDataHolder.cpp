#include "AI/cGlobalGraphDataHolder.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cGlobalGraphDataHolder::RetClassName() const
    {
        return "cGlobalGraphDataHolder";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cGlobalGraphDataHolderRegistrar(
        "cGlobalGraphDataHolder", cGlobalGraphDataHolder::MakeNew, 0x18, false);
}

#include "cd2/memory.h"

// CD2 0x8244AAF8: the class-factory constructor; the constructor stays out of line.
namespace AI
{
    RWS::CAttributeHandler *cGlobalGraphDataHolder::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cGlobalGraphDataHolder(packet);
    }
}
