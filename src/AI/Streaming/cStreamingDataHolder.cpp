#include "AI/cStreamingDataHolder.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cStreamingDataHolder::ms_pcStreamingDataHolderClass = &cStreamingDataHolder::StaticCreateClass();

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

#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cStreamingDataHolder::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cStreamingDataHolderClass = new Fun_Runtime::cClass(0x1D4A, "cStreamingDataHolder", 0x7C);
        return *cStreamingDataHolderClass;
    }
}
