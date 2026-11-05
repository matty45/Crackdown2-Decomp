#include "AI/cGlobalGraphDataHolder.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace AI
{
    const char *cGlobalGraphDataHolder::RetClassName() const
    {
        return "cGlobalGraphDataHolder";
    }

    static RWS::CClassFactory::CRegistrar cGlobalGraphDataHolderRegistrar(
        "cGlobalGraphDataHolder", cGlobalGraphDataHolder::MakeNew, 0x18, false);

    // CD2 0x8244AAF8: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cGlobalGraphDataHolder::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cGlobalGraphDataHolder(packet);
    }
}
