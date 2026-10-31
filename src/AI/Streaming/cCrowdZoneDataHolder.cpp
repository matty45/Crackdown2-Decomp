#include "AI/cCrowdZoneDataHolder.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace AI
{
    RWS::CAttributeHandler *cCrowdZoneDataHolder::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCrowdZoneDataHolder;
    }

    const char *cCrowdZoneDataHolder::RetClassName() const
    {
        return "cCrowdZoneDataHolder";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cCrowdZoneDataHolderRegistrar(
        "cCrowdZoneDataHolder", cCrowdZoneDataHolder::MakeNew, 0x7C, false);
}
