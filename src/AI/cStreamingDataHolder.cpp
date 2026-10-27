#include "AI/cStreamingDataHolder.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cStreamingDataHolder::ms_pcStreamingDataHolderClass = 0;

    cStreamingDataHolder::cStreamingDataHolder() {}

    const Fun_Runtime::cClass &cStreamingDataHolder::RetClass() const
    {
        return *ms_pcStreamingDataHolderClass;
    }

    const char *cStreamingDataHolder::RetClassName() const
    {
        return "cStreamingDataHolder";
    }

    bool cStreamingDataHolder::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcStreamingDataHolderClass->IsA(c);
    }

    RWS::CAttributeHandler *cStreamingDataHolder::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cStreamingDataHolder();
    }
}

static RWS::CClassFactory::CRegistrar cStreamingDataHolderRegistrar(
    "cStreamingDataHolder", AI::cStreamingDataHolder::MakeNew, 0x7C, false);