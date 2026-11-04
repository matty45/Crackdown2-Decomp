#include "AI/cCrowdZoneDataHolder.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace AI
{
    const Fun_Runtime::cClass &cCrowdZoneDataHolder::RetClass() const
    {
        return *ms_pcCrowdZoneDataHolderClass;
    }

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

namespace AI
{
    bool cCrowdZoneDataHolder::IsA(const Fun_Runtime::cClass &testClass) const
    {
        return ms_pcCrowdZoneDataHolderClass->IsA(testClass);
    }
}
